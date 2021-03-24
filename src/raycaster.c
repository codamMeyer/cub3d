#include <keyboard.h>
#include <map.h>
#include <math_utils.h>
#include <mlx.h>
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

void run()
{
	t_data data;

	data.mlx = mlx_init();
	data.window = mlx_new_window(data.mlx, screenWidth, screenHeight, "*** Raycaster ***");
	data.map.img = mlx_new_image(data.mlx, screenWidth, screenHeight);
	data.map.addr = mlx_get_data_addr(
		data.map.img, &data.map.bits_per_pixel, &data.map.line_length, &data.map.endian);
	data.worldMap.height = 25;
	data.worldMap.width = 25;
	data.worldMap.matrix = init_matrix(data.worldMap.height, data.worldMap.width);
	data.texture[WALL] = load_texture(&data, "textures/tree_wall.xpm");
	data.texture[SPRITE] = load_texture(&data, "textures/tree_snow1.xpm");

	if(!data.texture[WALL].initialized || !data.texture[SPRITE].initialized)
	{
		printf("NULL\n");
		return;
	}
	init_player(&data);
	mlx_hook(data.window, 2, 1L << 0, keypressed, &data);
	mlx_loop_hook(data.mlx, display, &data);
	mlx_loop(data.mlx);
}