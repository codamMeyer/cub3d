#include "vertical_detection.h"
#include <math.h>
#include <utils/direction.h>
#include <utils/map_utils.h>

t_position get_increment_for_vertical_detection(double ray_angle, double tan_angle)
{
	t_position increment;

	increment.x = GRID_SIZE;
	increment.y = GRID_SIZE * tan_angle;
	if (is_facing_west(ray_angle))
		increment.x *= -1;
	if (is_facing_east(ray_angle))
		increment.y *= -1;
	return (increment);
}

t_position get_first_vertical_intersection(t_player player, double ray_angle, double tan_angle)
{
	const int grid_boundary = floor(player.position.x / GRID_SIZE) * GRID_SIZE;
	const double small_value = 0.000001;
	t_position ray;
	double width;

	if (is_facing_west(ray_angle))
		ray.x = grid_boundary - small_value;
	else
		ray.x = grid_boundary + GRID_SIZE;
	width = (player.position.x - ray.x) * tan_angle;
	ray.y = player.position.y + width;
	return (ray);
}
