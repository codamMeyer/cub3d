#include "raycast_utils.h"
#include <math.h>
#include <utils/angle_utils.h>
#include <utils/grid_position.h>
#include <utils/math_utils.h>

t_bool	is_straight_left_or_right(double ray_angle)
{
	return (ray_angle == 0.0 || ray_angle == 180.0 || ray_angle == 360.0);
}

t_bool	is_straight_up_or_down(double ray_angle)
{
	return (ray_angle == 90.0 || ray_angle == 270.0);
}

t_bool	detect_hit(t_map worldMap, t_position pos, t_collider collider)
{
	t_grid_position	grid_pos;

	grid_pos = to_grid_position(worldMap, pos);
	grid_pos.x = max_i(grid_pos.x, 0);
	grid_pos.y = max_i(grid_pos.y, 0);
	grid_pos.x = min_i(grid_pos.x, worldMap.width - 1);
	grid_pos.y = min_i(grid_pos.y, worldMap.height - 1);
	return (worldMap.matrix[grid_pos.y][grid_pos.x] == (int)collider);
}

double	fix_fisheye_effect(double dist, double angle)
{
	return (dist * cos(degree_to_radians(angle)));
}

void	apply_increment_to_intersections(t_intersections *intersections)
{
	intersections->horizontal.x += intersections->hor_increment.x;
	intersections->horizontal.y += intersections->hor_increment.y;
	intersections->vertical.x += intersections->ver_increment.x;
	intersections->vertical.y += intersections->ver_increment.y;
}
