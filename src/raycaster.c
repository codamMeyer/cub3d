#include <errors.h>
#include <keyboard.h>
#include <libft.h>
#include <map.h>
#include <math_utils.h>
#include <mlx.h>
#include <parser.h>
#include <player.h>
#include <raycaster.h>
#include <sprite.h>
#include <stdio.h>
#include <wall_detection.h>

t_texture load_texture(t_data *data, char *filename)
{
	t_texture texture;
	int bit_per_pixel = 0;
	int size_line = 0;
	int endian = 0;
	texture.initialized = FALSE;
	texture.ptr = mlx_xpm_file_to_image(data->mlx, filename, &(texture.width), &(texture.height));
	if(!texture.ptr)
		return (texture);
	texture.data = mlx_get_data_addr(texture.ptr, &bit_per_pixel, &size_line, &endian);
	texture.initialized = TRUE;
	return (texture);
}

void ray_casting(t_data *data)
{
	const double ray_increment = (double)data->player.FOV / (double)data->player.plane_x;
	t_ray ray;
	ray.angle = data->player.angle + (data->player.FOV / 2);
	t_sprite sprites[10];

	t_sprite sprite;
	int i = 0;
	for(int col = 0; col < data->player.plane_x; col++)
	{
		find_and_draw_walls(col, data, &ray);

		sprite = find_sprites(data, ray.angle);
		if(is_valid_grid_position(data->worldMap, sprite.grid_pos))
		{
			if(i > 0)
			{
				if(sprite.grid_pos.x != sprites[i - 1].grid_pos.x ||
				   sprite.grid_pos.y != sprites[i - 1].grid_pos.y)
				{
					sprites[i] = sprite;
					++i;
				}
			}
			else
			{
				sprites[i] = sprite;
				i++;
			}
		}
		ray.angle -= ray_increment;
	}
	draw_sprites(data, &sprites[0], i);
	mlx_put_image_to_window(data->mlx, data->window, data->map.img, 0, 0);
}

static int display(t_data *data)
{
	ray_casting(data);
	// draw_map_2d(data);
	// draw_player(data);
	return (1);
}

static t_bool load_textures(t_data *data)
{
	data->textures[NO] = load_texture(data, data->textures[NO].filename);
	data->textures[SO] = load_texture(data, data->textures[SO].filename);
	data->textures[WE] = load_texture(data, data->textures[WE].filename);
	data->textures[EA] = load_texture(data, data->textures[EA].filename);
	data->textures[SP] = load_texture(data, data->textures[SP].filename);

	if(!data->textures[NO].initialized || !data->textures[SO].initialized ||
	   !data->textures[WE].initialized || !data->textures[EA].initialized ||
	   !data->textures[SP].initialized)
		return (FALSE);
	return (TRUE);
}

void close_window(t_data *data)
{
	free_matrix(data->worldMap.matrix, data->worldMap.height);
	mlx_destroy_window(data->mlx, data->window);
	exit(0);
}

void update_screen_resolution(t_data *data)
{
	int width;
	int height;
	mlx_get_screen_size(data->mlx, &width, &height);

	data->resolution.width = min_i(data->resolution.width, width);
	data->resolution.height = min_i(data->resolution.height, height);
	data->player.plane_x = data->resolution.width;
	data->player.plane_y = data->resolution.height;
}

t_status run(const char *filename)
{
	t_data data;
	t_status ret;

	init_player(&data);
	if((ret = parse_input(filename, &data)))
		return (ret);
	data.mlx = mlx_init();
	update_screen_resolution(&data);
	data.window = mlx_new_window(data.mlx, data.resolution.width, data.resolution.height, "CUB3D");
	data.map.img = mlx_new_image(data.mlx, data.resolution.width, data.resolution.height);
	data.map.addr = mlx_get_data_addr(
		data.map.img, &data.map.bits_per_pixel, &data.map.line_length, &data.map.endian);
	if(!load_textures(&data))
	{
		close_window(&data);
		return (FALSE);
	}
	mlx_hook(data.window, 2, 1L << 0, keypressed, &data);
	mlx_loop_hook(data.mlx, display, &data);
	mlx_loop(data.mlx);
	return (TRUE);
}