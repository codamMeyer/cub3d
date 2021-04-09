#include "raycast_utils.h"
#include <math.h>
#include <utils/math_utils.h>
#include <utils/math_utils2.h>

t_bool is_left_or_right(double ray_angle)
{
	if (ray_angle == 0.0 || ray_angle == 180.0 || ray_angle == 360.0)
		return (TRUE);
	return (FALSE);
}
t_bool is_up_or_down(double ray_angle)
{
	if (ray_angle == 90.0 || ray_angle == 270.0)
		return (TRUE);
	return (FALSE);
}

void keep_inside_map(t_grid_position *pos, t_map worldMap)
{
	pos->x = max_i(pos->x, 0);
	pos->y = max_i(pos->y, 0);
	pos->x = min_i(pos->x, worldMap.width - 1);
	pos->y = min_i(pos->y, worldMap.height - 1);
}

t_bool detect_hit(t_map worldMap, t_position pos, t_collider collider)
{
	t_grid_position grid_pos = to_grid_position(worldMap, pos);
	if (!is_valid_grid_position(worldMap, grid_pos))
		return (INVALID);
	keep_inside_map(&grid_pos, worldMap);
	if (worldMap.matrix[grid_pos.y][grid_pos.x] == (int)collider)
		return (TRUE);
	return (FALSE);
}

double fix_fisheye_effect(double dist, double angle)
{
	return (dist * cos(degree_to_radians(angle)));
}