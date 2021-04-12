#include "game.h"
#include <bmp/bmp.h>
#include <errors/errors.h>
#include <game/keyboard.h>
#include <libminift/libminift.h>
#include <math.h>
#include <mlx.h>
#include <parser/parser.h>
#include <player/player.h>
#include <src/sprite/sprite_render.h>
#include <stdio.h>
#include <utils/angle_utils.h>
#include <utils/map_utils.h>
#include <utils/math_utils.h>
#include <walls/walls.h>

void	cleanup(t_data *data)
{
	free_matrix(data->worldMap.matrix, data->worldMap.height);
	free(data->sprites);
}

void	close_window(t_data *data)
{
	cleanup(data);
	mlx_destroy_window(data->img.mlx, data->img.window);
	exit(0);
}

t_texture	load_texture(t_data *data, char *filename)
{
	t_texture	texture;
	int			endian;

	endian = 0;
	texture.initialized = FALSE;
	texture.ptr = mlx_xpm_file_to_image(data->img.mlx, filename, \
										&(texture.width), &(texture.height));
	if (!texture.ptr)
		return (texture);
	texture.data = mlx_get_data_addr(texture.ptr, &texture.bit_per_pixel, \
							&texture.line_size, &endian);
	texture.initialized = TRUE;
	return (texture);
}

void	ray_casting(t_data *data)
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
}

static int	display(t_data *data)
{
	ray_casting(data);
	return (1);
}

static t_bool	load_textures(t_data *data)
{
	data->textures[NO] = load_texture(data, data->textures[NO].filename);
	data->textures[SO] = load_texture(data, data->textures[SO].filename);
	data->textures[WE] = load_texture(data, data->textures[WE].filename);
	data->textures[EA] = load_texture(data, data->textures[EA].filename);
	data->textures[SP] = load_texture(data, data->textures[SP].filename);
	if (!data->textures[NO].initialized || !data->textures[SO].initialized || \
		!data->textures[WE].initialized || !data->textures[EA].initialized || \
		!data->textures[SP].initialized)
		return (FALSE);
	return (TRUE);
}

static void	update_screen_resolution(t_data *data)
{
	int	width;
	int	height;

	mlx_get_screen_size(data->img.mlx, &width, &height);
	data->screen.width = min_i(data->screen.width, width);
	data->screen.height = min_i(data->screen.height, height);
}

static t_bool	init_window(t_data *data)
{
	data->img.mlx = mlx_init();
	if (!data->img.mlx)
		return (FALSE);
	update_screen_resolution(data);
	data->img.window = mlx_new_window(data->img.mlx, data->screen.width, \
						data->screen.height, "CUB3D");
	if (!data->img.window)
		return (FALSE);
	data->img.ptr = mlx_new_image(data->img.mlx, \
									data->screen.width, data->screen.height);
	if (!data->img.ptr)
		return (FALSE);
	data->img.addr = mlx_get_data_addr(data->img.ptr, &data->img.bits_per_pixel, \
									&data->img.line_length, &data->img.endian);
	if (!data->img.addr)
		return (FALSE);
	return (TRUE);
}

int	red_cross(t_data *data)
{
	close_window(data);
	return (1);
}

t_status	run(const char *filename, t_bool save)
{
	const unsigned int	key_mask = (1L << 0);
	const unsigned int	notify_mask = (1L << 17);
	t_data				data;
	t_status			ret;

	data.player = create_player();
	ret = parse_input(filename, &data);
	if (ret != SUCCESS)
		return (ret);
	if (!init_window(&data))
		return (INIT_WINDOW_ERROR);
	if (!load_textures(&data))
	{
		close_window(&data);
		return (TEXTURE_INFO_ERROR);
	}
	data.player.dist_to_plane = (data.screen.width / 2.0) \
							/ tan(degree_to_radians(data.player.FOV / 2.0));
	data.save = save;
	mlx_hook(data.img.window, KEY_PRESS_EVENT, key_mask, keypressed, &data);
	mlx_hook(data.img.window, CLIENT_MSG_EVENT, notify_mask, red_cross, &data);
	mlx_loop_hook(data.img.mlx, display, &data);
	mlx_loop(data.img.mlx);
	return (TRUE);
}
