#include "vertical_detection.h"
#include <math.h>
#include <utils/direction.h>
#include <utils/map_utils.h>

double get_x_increment_for_vertical_detection(double ray_angle)
{
	double x_increment;
	if (is_facing_west(ray_angle))
		x_increment = -GRID_SIZE;
	else
		x_increment = GRID_SIZE;
	return (x_increment);
}

double get_y_increment_for_vertical_detection(double ray_angle, double tan_angle)
{
	double y_increment = GRID_SIZE * tan_angle;
	if (is_facing_east(ray_angle))
		y_increment *= -1;
	return (y_increment);
}

t_position get_first_vertical_intersection(t_player player, double ray_angle, double tan_angle)
{
	t_position ray;
	double width;

	if (is_facing_west(ray_angle))
		ray.x = floor(player.position.x / GRID_SIZE) * (GRID_SIZE) - (1e-6);
	else
		ray.x = floor(player.position.x / GRID_SIZE) * (GRID_SIZE) + GRID_SIZE;
	width = (player.position.x - ray.x) * tan_angle;
	ray.y = player.position.y + width;

	return (ray);
}
