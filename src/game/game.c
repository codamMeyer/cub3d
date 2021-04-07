#include <bmp/bmp.h>
#include <game/game.h>
#include <game/player.h>
#include <game/sprite.h>
#include <game/wall_detection.h>
#include <libft/libft.h>
#include <mlx.h>
#include <parser/parser.h>
#include <stdio.h>
#include <utils/errors.h>
#include <utils/keyboard.h>
#include <utils/map_utils.h>
#include <utils/math_utils.h>

t_texture load_texture(t_data *data, char *filename)
{
	t_texture texture;
	int endian = 0;
	texture.initialized = FALSE;
	texture.ptr =
		mlx_xpm_file_to_image(data->img.mlx, filename, &(texture.width), &(texture.height));
	if (!texture.ptr)
		return (texture);
	texture.data =
		mlx_get_data_addr(texture.ptr, &texture.bit_per_pixel, &texture.line_size, &endian);
	texture.initialized = TRUE;
	return (texture);
}

void find_and_draw_sprites(int col, t_data *data, t_ray *ray)
{
	t_list *sprites;

	sprites = NULL;
	find_sprites(data, &sprites, ray->angle);

	t_list *cur;
	cur = sprites;
	while (cur != NULL)
	{
		get_sprite_values(data, cur->content);
		draw_sprites_vertical_line(data, col, 400, *((t_sprite *)cur->content));
		cur = cur->next;
	}
	ft_lstclear(&sprites, free);
}

void ray_casting(t_data *data)
{
	const double ray_increment = (double)data->player.FOV / (double)data->screen.width;
	t_ray ray;

	ray.angle = data->player.angle + (data->player.FOV / 2);

	for (int col = 0; col < data->screen.width; col++)
	{
		find_and_draw_walls(col, data, &ray); // return dist
		find_and_draw_sprites(col, data, &ray);
		ray.angle -= ray_increment;
	}

	save_image(data);
	mlx_put_image_to_window(data->img.mlx, data->img.window, data->img.ptr, 0, 0);
}

static int display(t_data *data)
{
	ray_casting(data);
	return (1);
}

static t_bool load_textures(t_data *data)
{
	data->textures[NO] = load_texture(data, data->textures[NO].filename);
	data->textures[SO] = load_texture(data, data->textures[SO].filename);
	data->textures[WE] = load_texture(data, data->textures[WE].filename);
	data->textures[EA] = load_texture(data, data->textures[EA].filename);
	data->textures[SP] = load_texture(data, data->textures[SP].filename);
	data->textures[SHADOW] = load_texture(data, "./textures/tree_wall_shadow.xpm");

	if (!data->textures[NO].initialized || !data->textures[SO].initialized ||
		!data->textures[WE].initialized || !data->textures[EA].initialized ||
		!data->textures[SP].initialized)
		return (FALSE);
	return (TRUE);
}

static void update_screen_resolution(t_data *data)
{
	int width;
	int height;
	mlx_get_screen_size(data->img.mlx, &width, &height);
	data->screen.width = min_i(data->screen.width, width);
	data->screen.height = min_i(data->screen.height, height);
}

static t_bool init_window(t_data *data)
{
	data->img.mlx = mlx_init();
	if (!data->img.mlx)
		return (FALSE);

	update_screen_resolution(data);
	data->img.window =
		mlx_new_window(data->img.mlx, data->screen.width, data->screen.height, "CUB3D");
	if (!data->img.window)
		return (FALSE);

	data->img.ptr = mlx_new_image(data->img.mlx, data->screen.width, data->screen.height);
	if (!data->img.ptr)
		return (FALSE);

	data->img.addr = mlx_get_data_addr(data->img.ptr,
									   &data->img.bits_per_pixel,
									   &data->img.line_length,
									   &data->img.endian);
	if (!data->img.addr)
		return (FALSE);

	return (TRUE);
}

int red_cross(t_data *data)
{
	close_window(data);
	return (1);
}

t_status run(const char *filename, t_bool save)
{
	t_data data;
	t_status ret;

	init_player(&data);
	if ((ret = parse_input(filename, &data)))
		return (ret);
	if (!init_window(&data))
		return (INIT_WINDOW_ERROR);
	if (!load_textures(&data))
	{
		close_window(&data);
		return (FALSE);
	}
	data.save = save;
	mlx_hook(data.img.window, KEY_PRESS_EVENT, KEY_PRESS_MASK, keypressed, &data);
	mlx_hook(data.img.window, CLIENT_MESSAGE_EVENT, STRUCT_NOTIFY_MASK, red_cross, &data);
	mlx_loop_hook(data.img.mlx, display, &data);
	mlx_loop(data.img.mlx);
	return (TRUE);
}

// t_sprite sprites[10];

// t_bool found = FALSE;
// t_sprite sprite;
// int i = 0;
// sprites[0].center.x = -1;
// sprites[0].center.y = -1;
// sprites[0].grid_pos.y = -1;
// sprites[0].grid_pos.y = -1;
// for (int col = 0; col < data->screen.width; col++)
// {
// 	sprite = find_sprites(data, ray.angle);
// 	if (is_valid_grid_position(data->worldMap, sprite.grid_pos))
// 	{
// 		if (i > 0)
// 		{
// 			if (sprite.grid_pos.x != sprites[i - 1].grid_pos.x ||
// 				sprite.grid_pos.y != sprites[i - 1].grid_pos.y)
// 			{
// 				sprites[i] = sprite;
// 				++i;
// 			}
// 		}
// 		else
// 		{
// 			sprites[i] = sprite;
// 			i++;
// 		}
// 		found = TRUE;
// 	}
// 	ray.angle -= ray_increment;
// }
// ray.angle = data->player.angle + (data->player.FOV / 2);
// get_sprite_values(data, &sprites[0]);