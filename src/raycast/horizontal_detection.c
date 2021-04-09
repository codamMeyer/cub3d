#include "horizontal_detection.h"
#include <math.h>
#include <utils/direction.h>
#include <utils/map_utils.h>

t_position get_first_horizontal_intersection(t_player player, double ray_angle, double tan_angle)
{
	t_position ray;
	double width;

	if (is_facing_north(ray_angle))
		ray.y = floor(player.position.y / GRID_SIZE) * (GRID_SIZE) - (1e-6);
	else
		ray.y = floor(player.position.y / GRID_SIZE) * (GRID_SIZE) + GRID_SIZE;
	width = (player.position.y - ray.y) / tan_angle;
	ray.x = player.position.x + width;

	return (ray);
}

double get_y_increment_for_horizontal_detection(double ray_angle)
{
	double y_increment;
	if (is_facing_north(ray_angle))
		y_increment = -GRID_SIZE;
	else
		y_increment = GRID_SIZE;
	return (y_increment);
}

double get_x_increment_for_horizontal_detection(double ray_angle, double tan_angle)
{
	double x_increment = GRID_SIZE / tan_angle;
	if (is_facing_south(ray_angle))
		x_increment *= -1;
	return (x_increment);
}
