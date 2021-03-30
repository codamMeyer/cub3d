#include <game/ray_casting_logic.h>
#include <game/render.h>
#include <math.h>
#include <stdio.h>
#include <utils/direction.h>
#include <utils/map_utils.h>
#include <utils/math_utils.h>

static t_bool hit_wall(t_map worldMap, t_position pos)
{
	t_grid_position grid_pos = to_grid_position(worldMap, pos);
	if(!is_valid_grid_position(worldMap, grid_pos))
		return (INVALID);
	grid_pos.x = max_i(grid_pos.x, 0);
	grid_pos.y = max_i(grid_pos.y, 0);
	grid_pos.x = min_i(grid_pos.x, worldMap.width - 1);
	grid_pos.y = min_i(grid_pos.y, worldMap.height - 1);

	if(worldMap.matrix[grid_pos.y][grid_pos.x] == WALL)
		return (TRUE);
	return (FALSE);
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

t_bool is_straight_left_or_right(t_position *ray, double ray_angle)
{
	if(ray_angle == 0.0 || ray_angle == 180.0 || ray_angle == 360.0)
	{
		ray->x = INVALID;
		ray->y = INVALID;
		return (TRUE);
	}
	return (FALSE);
}

double get_y_increment_for_horizontal_detection(double ray_angle)
{
	double y_increment;
	if(is_facing_north(ray_angle))
		y_increment = -GRID_SIZE;
	else
		y_increment = GRID_SIZE;
	return (y_increment);
}

double get_x_increment_for_horizontal_detection(double ray_angle, double tan_angle)
{
	double x_increment = GRID_SIZE / tan_angle;
	if(is_facing_south(ray_angle))
		x_increment *= -1;
	return (x_increment);
}

t_position find_wall(t_map worldMap, double x_increment, double y_increment, t_position ray)
{
	while(!hit_wall(worldMap, ray))
	{
		ray.x += x_increment;
		ray.y += y_increment;
		ray = keep_inside_map(worldMap, ray);
	}

	return (ray);
}

double get_x_increment_for_vertical_detection(double ray_angle)
{
	double x_increment;
	if(is_facing_west(ray_angle))
		x_increment = -GRID_SIZE;
	else
		x_increment = GRID_SIZE;
	return (x_increment);
}

double get_y_increment_for_vertical_detection(double ray_angle, double tan_angle)
{
	double y_increment = GRID_SIZE * tan_angle;
	if(is_facing_east(ray_angle))
		y_increment *= -1;
	return (y_increment);
}

t_bool is_straight_up_or_down(t_position *ray, double ray_angle)
{
	if(ray_angle == 90.0 || ray_angle == 270.0)
	{
		ray->x = INVALID;
		ray->y = INVALID;
		return (TRUE);
	}
	return (FALSE);
}

t_position get_first_vertical_intersection(t_player player, double ray_angle, double tan_angle)
{
	t_position ray;
	double width;

	if(is_facing_west(ray_angle))
		ray.x = floor(player.position.x / GRID_SIZE) * (GRID_SIZE) - (1e-6);
	else
		ray.x = floor(player.position.x / GRID_SIZE) * (GRID_SIZE) + GRID_SIZE;
	width = (player.position.x - ray.x) * tan_angle;
	ray.y = player.position.y + width;

	return (ray);
}

t_position get_first_horizontal_intersection(t_player player, double ray_angle, double tan_angle)
{
	t_position ray;
	double width;

	if(is_facing_north(ray_angle))
		ray.y = floor(player.position.y / GRID_SIZE) * (GRID_SIZE) - (1e-6);
	else
		ray.y = floor(player.position.y / GRID_SIZE) * (GRID_SIZE) + GRID_SIZE;
	width = (player.position.y - ray.y) / tan_angle;
	ray.x = player.position.x + width;

	return (ray);
}
