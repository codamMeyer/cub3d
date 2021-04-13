#include "game.h"
#include <bmp/bmp.h>
#include <errors/errors.h>
#include <game/keyboard.h>
#include <libminift/libminift.h>
#include <math.h>
#include <mlx.h>
#include <parser/parser.h>
#include <player/player.h>
#include <player/movement.h>
#include <src/sprite/sprite_render.h>
#include <stdio.h>
#include <utils/angle_utils.h>
#include <utils/map_utils.h>
#include <utils/math_utils.h>
#include <walls/walls.h>
#include "game_utils.h"

static int	raycast(t_data *data)
{
	const double	ray_increment = \
					(double)data->player.FOV / (double)data->screen.width;
	t_ray			ray;
	double			dist;
	int				col;

	ray.angle = data->player.angle + (data->player.FOV / 2);
	col = 0;
	while (col < data->screen.width)
	{
		dist = find_and_draw_walls(col, data, &ray);
		find_and_draw_sprites(col, data, &ray, dist);
		ray.angle -= ray_increment;
		++col;
	}
	mlx_put_image_to_window(data->img.mlx, data->img.window, \
							data->img.ptr, 0, 0);
	save_image(data->screen, data->img.addr, data->save);
	return (1);
}

static void	update_screen_resolution(t_data *data)
{
	int	width;
	int	height;

	mlx_get_screen_size(data->img.mlx, &width, &height);
	data->screen.width = min_i(data->screen.width, width);
	data->screen.height = min_i(data->screen.height, height);
	data->player.dist_to_plane = (data->screen.width / 2.0) \
							/ tan(degree_to_radians(data->player.FOV / 2.0));
}

static int	update_frame(t_data *data)
{
	raycast(data);
	update(&data->player, data->worldMap);
	return (1);
}

static t_status	init_window(t_data *data)
{
	data->img.mlx = mlx_init();
	if (!data->img.mlx)
		return (INIT_WINDOW_ERROR);
	update_screen_resolution(data);
	data->img.window = mlx_new_window(data->img.mlx, data->screen.width, \
						data->screen.height, "CUB3D");
	if (!data->img.window)
		return (INIT_WINDOW_ERROR);
	data->img.ptr = mlx_new_image(data->img.mlx, \
									data->screen.width, data->screen.height);
	if (!data->img.ptr)
		return (INIT_WINDOW_ERROR);
	data->img.addr = mlx_get_data_addr(data->img.ptr, &data->img.bits_per_pixel, \
									&data->img.line_length, &data->img.endian);
	if (!data->img.addr)
		return (INIT_WINDOW_ERROR);
	return (SUCCESS);
}

void	run(const char *filename, t_bool save)
{
	const unsigned int	press = (1L << 0);
	const unsigned int	notify = (1L << 17);
	const unsigned int	release = (1L << 1);
	t_data				data;
	t_status			ret;

	data.player = create_player();
	ret = SUCCESS;
	ret = parse_input(filename, &data);
	if (ret == SUCCESS)
		ret = init_window(&data);
	if (ret == SUCCESS)
		ret = load_textures(&data);
	if (ret != SUCCESS)
		close_window(&data, ret);
	data.save = save;
	mlx_hook(data.img.window, KEY_PRESS_EVENT, press, key_pressed, &data);
	mlx_hook(data.img.window, KEY_RELEASE_EVENT, release, key_released, &data);
	mlx_hook(data.img.window, CLIENT_MSG_EVENT, notify, red_cross, &data);
	mlx_loop_hook(data.img.mlx, update_frame, &data);
	mlx_loop(data.img.mlx);
	return ;
}
