#include <assert.h>
#include <direction.h>
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

static t_bool hit_obstacle(t_map worldMap, t_position pos)
{
	t_grid_position grid_pos = to_grid_position(worldMap, pos);
	if(grid_pos.x == INVALID || grid_pos.y == INVALID)
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
	if(angle > 359)
		angle -= 360;
	if(angle < 0)
		angle += 360;
	return angle;
}

static t_bool is_straight_left_or_right(t_position *ray, double ray_angle)
{
	if(ray_angle == 0.0 || ray_angle == 180.0 || ray_angle == 360.0)
	{
		ray->x = INVALID;
		ray->y = INVALID;
		return (TRUE);
	}
	return (FALSE);
}

static double get_y_increment_for_horizontal_detection(double ray_angle)
{
	double y_increment;
	if(is_facing_north(ray_angle))
		y_increment = -GRID_SIZE;
	else
		y_increment = GRID_SIZE;
	return (y_increment);
}

static double get_x_increment_for_horizontal_detection(double ray_angle, double tan_angle)
{
	double x_increment = GRID_SIZE / tan_angle;
	if(is_facing_south(ray_angle))
		x_increment *= -1;
	return (x_increment);
}

static t_position
get_first_horizontal_intersection(t_player player, double ray_angle, double tan_angle)
{
	t_position ray;
	double width;

	if(is_facing_north(ray_angle))
		ray.y = floor(player.position.y / GRID_SIZE) * (GRID_SIZE)-1;
	else
		ray.y = floor(player.position.y / GRID_SIZE) * (GRID_SIZE) + GRID_SIZE;
	width = (player.position.y - ray.y) / tan_angle;
	ray.x = player.position.x + width;

	return (ray);
}

static t_position
find_obstacle(t_data *data, t_map worldMap, double x_increment, double y_increment, t_position ray)
{
	(void)data;
	while(!hit_obstacle(worldMap, ray))
	{
		ray.x += x_increment;
		ray.y += y_increment;
		ray = keep_inside_map(worldMap, ray);
		// draw_square(&data->map, 5, ray.x, ray.y, BLUE);
	}

	return (ray);
}

t_position find_horizontal_line(t_data *data, double ray_angle)
{
	ray_angle = fixAng(ray_angle);
	t_position ray;
	if(is_straight_left_or_right(&ray, ray_angle))
		return (ray);
	double tan_angle = tan(degree_to_radians(ray_angle));
	double y_increment = get_y_increment_for_horizontal_detection(ray_angle);
	double x_increment = get_x_increment_for_horizontal_detection(ray_angle, tan_angle);
	ray = get_first_horizontal_intersection(data->player, ray_angle, tan_angle);
	return (find_obstacle(data, data->worldMap, x_increment, y_increment, ray));
}

static double get_x_increment_for_vertical_detection(double ray_angle)
{
	double x_increment;
	if(is_facing_west(ray_angle))
		x_increment = -GRID_SIZE;
	else
		x_increment = GRID_SIZE;
	return (x_increment);
}

static double get_y_increment_for_vertical_detection(double ray_angle, double tan_angle)
{
	double y_increment = GRID_SIZE * tan_angle;
	if(is_facing_east(ray_angle))
		y_increment *= -1;
	return (y_increment);
}

static t_bool is_straight_up_or_down(t_position *ray, double ray_angle)
{
	if(ray_angle == 90.0 || ray_angle == 270.0)
	{
		ray->x = INVALID;
		ray->y = INVALID;
		return (TRUE);
	}
	return (FALSE);
}

static t_position
get_first_vertical_intersection(t_player player, double ray_angle, double tan_angle)
{
	t_position ray;
	double width;

	if(is_facing_west(ray_angle))
		ray.x = floor(player.position.x / GRID_SIZE) * (GRID_SIZE)-1;
	else
		ray.x = floor(player.position.x / GRID_SIZE) * (GRID_SIZE) + GRID_SIZE;
	width = (player.position.x - ray.x) * tan_angle;
	ray.y = player.position.y + width;

	return (ray);
}

t_position find_vertical_line(t_data *data, double ray_angle)
{
	ray_angle = fixAng(ray_angle);
	t_position ray;

	if(is_straight_up_or_down(&ray, ray_angle))
		return (ray);
	double tan_angle = tan(degree_to_radians(ray_angle));
	double x_increment = get_x_increment_for_vertical_detection(ray_angle);
	double y_increment = get_y_increment_for_vertical_detection(ray_angle, tan_angle);
	ray = get_first_vertical_intersection(data->player, ray_angle, tan_angle);
	return (find_obstacle(data, data->worldMap, x_increment, y_increment, ray));
}

double get_wall_distance(t_position ray_coord, t_position player_coord)
{
	const double x_diff = (player_coord.x - ray_coord.x) * (player_coord.x - ray_coord.x);
	const double y_diff = (player_coord.y - ray_coord.y) * (player_coord.y - ray_coord.y);
	return (sqrt(x_diff + y_diff));
}

void draw_ceiling_slice(t_data *data, int slice_col, int wall_top)
{
	int i = 0;
	while(i < wall_top)
	{
		my_mlx_pixel_put(&data->map, slice_col, i, BLUE);
		++i;
	}
}

void draw_wall_slice(t_data *data, int slice_col, int wall_bottom, int wall_top)
{
	int i = wall_top;
	while(i < wall_bottom)
	{
		my_mlx_pixel_put(&data->map, slice_col, i, RED);
		++i;
	}
}

void draw_floor_slice(t_data *data, int slice_col, int wall_bottom)
{
	int i = wall_bottom;
	while(i < data->player.plane_y)
	{
		my_mlx_pixel_put(&data->map, slice_col, i, DARK_BLUE);
		++i;
	}
}

void draw_slice(t_data *data, double dist, int slice_col)
{
	const double dist_to_plane =
		(data->player.plane_x / 2) / tan(degree_to_radians(data->player.FOV / 2));
	double wall_height = (GRID_SIZE / dist) * dist_to_plane;
	wall_height = min_d(wall_height, data->player.plane_y);
	const double wall_top = (data->player.plane_y / 2) - (wall_height / 2);
	const double wall_bottom = wall_top + wall_height;
	draw_ceiling_slice(data, slice_col, wall_top);
	draw_wall_slice(data, slice_col, wall_bottom, wall_top);
	draw_floor_slice(data, slice_col, wall_bottom);
}

static t_bool valid_position(t_position position)
{
	return (position.x != INVALID && position.y != INVALID);
}

static double fix_fisheye_effect(double closer_wall, double ray_angle)
{
	return (closer_wall * cos(degree_to_radians(ray_angle)));
}

static double find_closer_wall(t_position h_intersection,
							   t_position v_intersection,
							   t_player player,
							   double ray_angle)
{
	double closer_wall;
	if(!valid_position(h_intersection))
		closer_wall = get_wall_distance(v_intersection, player.position);
	else if(!valid_position(v_intersection))
		closer_wall = get_wall_distance(h_intersection, player.position);
	else
		closer_wall = min_d(get_wall_distance(v_intersection, player.position),
							get_wall_distance(h_intersection, player.position));
	ray_angle = fixAng(player.angle - ray_angle);
	return (fix_fisheye_effect(closer_wall, ray_angle));
}

static void rayCasting(t_data *data)
{
	double ray_angle = data->player.angle + (data->player.FOV / 2);
	const double ray_increment = (double)data->player.FOV / (double)data->player.plane_x;
	t_position h_intersection;
	t_position v_intersection;
	double closer_wall;

	for(int col = 0; col < data->player.plane_x; col++)
	{
		h_intersection = find_horizontal_line(data, ray_angle);
		v_intersection = find_vertical_line(data, ray_angle);
		closer_wall = find_closer_wall(h_intersection, v_intersection, data->player, ray_angle);

		draw_slice(data, closer_wall, col);

		ray_angle -= ray_increment;
	}
	mlx_put_image_to_window(data->mlx, data->window, data->map.img, 0, 0);
}

static int display(t_data *data)
{
	paint_background(screenWidth, screenHeight, data);
	rayCasting(data);
	draw_map_2d(data);
	draw_player(data);
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

	data.worldMap.matrix[3][3] = 1;
	data.worldMap.matrix[3][4] = 1;

	init_player(&data);
	mlx_hook(data.window, 2, 1L << 0, keypressed, &data);
	mlx_loop_hook(data.mlx, display, &data);
	mlx_loop(data.mlx);
}
