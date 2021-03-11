#include <assert.h>
#include <keyboard.h>
#include <map.h>
#include <math.h>
#include <math_utils.h>
#include <mlx.h>
#include <player.h>
#include <raycaster.h>
#include <stdio.h>
#include <stdlib.h>
#include <utils.h>
#include <direction.h>
#include <math_utils.h>

static t_bool hit_obstacle(t_map worldMap, t_position pos)
{
	t_grid_position grid_pos = to_grid_position(worldMap, pos);
	if (grid_pos.x == INVALID || grid_pos.y == INVALID)
		return (1);
	grid_pos.x = max_i(grid_pos.x, 0);
	grid_pos.y = max_i(grid_pos.y, 0);
	grid_pos.x = min_i(grid_pos.x, worldMap.width - 1);
	grid_pos.y = min_i(grid_pos.y, worldMap.height - 1);

	return (worldMap.matrix[grid_pos.y][grid_pos.x]);
}

static t_position keep_inside_map(t_map worldMap, t_position pos)
{
	t_position new_pos = pos;
	new_pos.x = max_d(new_pos.x, 0.0);
	new_pos.y = max_d(new_pos.y, 0.0);
	new_pos.x = min_d(new_pos.x, (double)worldMap.width * GRID_SIZE);
	new_pos.y = min_d(new_pos.y, (double)worldMap.height * GRID_SIZE);
	return (new_pos);
}

static double fixAng(double angle)
{
	if (angle > 359)
		angle -= 360;
	if (angle < 0)
		angle += 360;
	return angle;
}

t_position find_horizontal_line(t_data *data, double ray_angle)
{
	ray_angle = fixAng(ray_angle);
	t_position ray;
	if (ray_angle == 0.0 || ray_angle == 180.0 || ray_angle == 360.0)
	{
		ray.x = INVALID;
		ray.y = INVALID;
		return (ray);
	}

	double tan_angle = tan(degree_to_radians(ray_angle));
	int y_increment;

	if (is_facing_north(ray_angle))
		y_increment = -GRID_SIZE;
	else
		y_increment = GRID_SIZE;

	int x_increment = GRID_SIZE / tan_angle;

	if (is_facing_south(ray_angle))
		x_increment *= -1;

	double width;

	if (is_facing_north(ray_angle))
	{
		ray.y = floor(data->player.position.y / GRID_SIZE) * (GRID_SIZE)-1;
	}
	else
	{
		ray.y = floor(data->player.position.y / GRID_SIZE) * (GRID_SIZE) + GRID_SIZE;
	}
	width = (data->player.position.y - ray.y) / tan_angle;
	ray.x = data->player.position.x + width;

	while (!hit_obstacle(data->worldMap, ray))
	{
		ray.x += x_increment;
		ray.y += y_increment;
		ray = keep_inside_map(data->worldMap, ray);
		// draw_square(&data->map, 5, ray.x, ray.y, BLUE);
	}
	return (ray);
}

t_position find_vertical_line(t_data *data, double ray_angle)
{
	ray_angle = fixAng(ray_angle);
	t_position ray;

	if (ray_angle == 90.0 || ray_angle == 270.0)
	{
		ray.x = INVALID;
		ray.y = INVALID;
		return (ray);
	}

	double tan_angle = tan(degree_to_radians(ray_angle));
	int x_increment;

	if (is_facing_west(ray_angle))
		x_increment = -GRID_SIZE;
	else
		x_increment = GRID_SIZE;

	int y_increment = GRID_SIZE * tan_angle;

	if (is_facing_east(ray_angle))
		y_increment *= -1;

	double width;

	if (is_facing_west(ray_angle))
		ray.x = floor(data->player.position.x / GRID_SIZE) * (GRID_SIZE)-1;
	else
		ray.x = floor(data->player.position.x / GRID_SIZE) * (GRID_SIZE) + GRID_SIZE;
	width = (data->player.position.x - ray.x) * tan_angle;
	ray.y = data->player.position.y + width;

	while (!hit_obstacle(data->worldMap, ray))
	{
		ray.x += x_increment;
		ray.y += y_increment;
		ray = keep_inside_map(data->worldMap, ray);
		// draw_square(&data->map, 5, ray.x, ray.y, RED);
	}
	return (ray);
}

static void rayCasting(t_data *data)
{
	double start_ray_angle = data->player.angle - (data->player.FOV / 2);
	double end_ray_angle = data->player.angle + (data->player.FOV / 2);
	const double ray_increment = (double)data->player.FOV / (double)320;
	for (double ray_angle = start_ray_angle; ray_angle <= end_ray_angle; ray_angle += ray_increment)
	{
		find_horizontal_line(data, ray_angle);
		find_vertical_line(data, ray_angle);
	} // checking Vertical lines
}

static int display(t_data *data)
{
	paint_background(screenWidth, screenHeight, data);

	draw_map_2d(data);
	draw_player(data);
	rayCasting(data);
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

	data.worldMap.height = mapHeight;
	data.worldMap.width = mapWidth;
	data.worldMap.matrix = init_matrix(data.worldMap.height, data.worldMap.width);

	data.worldMap.matrix[5][5] = 1;
	data.worldMap.matrix[5][6] = 1;
	data.worldMap.matrix[5][7] = 1;
	data.worldMap.matrix[5][8] = 1;

	data.worldMap.matrix[19][20] = 1;
	data.worldMap.matrix[20][20] = 1;
	data.worldMap.matrix[21][20] = 1;
	data.worldMap.matrix[22][20] = 1;

	init_player(&data);
	mlx_hook(data.window, 2, 1L << 0, keypressed, &data);
	mlx_loop_hook(data.mlx, display, &data);
	mlx_loop(data.mlx);
}
