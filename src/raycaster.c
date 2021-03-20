#include <direction.h>
#include <keyboard.h>
#include <map.h>
#include <math.h>
#include <math_utils.h>
#include <mlx.h>
#include <player.h>
#include <ray_casting_logic.h>
#include <raycaster.h>
#include <render.h>
#include <stdio.h>
#include <stdlib.h>
#include <utils.h>

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

double get_wall_distance(t_position ray_coord, t_position player_coord)
{
	const double x_diff = (player_coord.x - ray_coord.x) * (player_coord.x - ray_coord.x);
	const double y_diff = (player_coord.y - ray_coord.y) * (player_coord.y - ray_coord.y);
	return (sqrt(x_diff + y_diff));
}

static double fix_fisheye_effect(double closest_wall, double ray_angle)
{
	return (closest_wall * cos(degree_to_radians(ray_angle)));
}

void find_closest_wall(t_position h_intersection,
					   t_position v_intersection,
					   t_player player,
					   t_ray *ray)
{
	const double v_dist = get_wall_distance(v_intersection, player.position);
	const double h_dist = get_wall_distance(h_intersection, player.position);
	const double angle = fix_angle(player.angle - ray->angle);

	if(v_dist < h_dist)
	{
		ray->pos = v_intersection;
		ray->distance = fix_fisheye_effect(v_dist, angle);
		ray->orientation = VERTICAL;
	}
	else
	{
		ray->pos = h_intersection;
		ray->distance = fix_fisheye_effect(h_dist, angle);
		ray->orientation = HORIZONTAL;
	}
}

void rayCasting(t_data *data)
{
	const double ray_increment = (double)data->player.FOV / (double)data->player.plane_x;
	t_ray ray;
	ray.angle = data->player.angle + (data->player.FOV / 2);
	for(int col = 0; col < data->player.plane_x; col++)
	{
		ray.angle = fix_angle(ray.angle);
		t_position h_intersection = find_horizontal_line(data, ray.angle);
		t_position v_intersection = find_vertical_line(data, ray.angle);

		find_closest_wall(h_intersection, v_intersection, data->player, &ray);

		draw_slice(data, col, ray);
		ray.angle -= ray_increment;
	}
	mlx_put_image_to_window(data->mlx, data->window, data->map.img, 0, 0);
}

static int display(t_data *data)
{
	paint_background(screenWidth, screenHeight, data);
	rayCasting(data);
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

	data.texture = load_texture(&data, "textures/tree_wall.xpm");
	if(!data.texture.initialized)
	{
		printf("NULL\n");
		return;
	}

	init_player(&data);
	mlx_hook(data.window, 2, 1L << 0, keypressed, &data);
	mlx_loop_hook(data.mlx, display, &data);
	mlx_loop(data.mlx);
}