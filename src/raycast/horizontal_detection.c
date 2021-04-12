#include "horizontal_detection.h"
#include <math.h>
#include <utils/direction.h>
#include <utils/map_utils.h>

t_position	get_first_horizontal_intersection(t_player player,
												double ray_angle,
												double tan_angle)
{
	t_position	ray;
	double		width;

	if (is_facing_north(ray_angle))
		ray.y = floor(player.position.y / GRID_SIZE) * (GRID_SIZE) - (1e-6);
	else
		ray.y = floor(player.position.y / GRID_SIZE) * (GRID_SIZE) + GRID_SIZE;
	width = (player.position.y - ray.y) / tan_angle;
	ray.x = player.position.x + width;
	return (ray);
}

t_position	get_increment_for_horizontal_detection(double ray_angle,
													double tan_angle)
{
	t_position	increment;

	increment.x = GRID_SIZE / tan_angle;
	increment.y = GRID_SIZE;
	if (is_facing_north(ray_angle))
		increment.y *= -1;
	if (is_facing_south(ray_angle))
		increment.x *= -1;
	return (increment);
}
