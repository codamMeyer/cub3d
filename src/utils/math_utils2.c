#include "math_utils2.h"
#include "map_utils.h"
#include <math.h>

t_grid_position to_grid_position(t_map worldMap, t_position pos)
{
	t_grid_position grid_pos = {.x = pos.x / GRID_SIZE, .y = pos.y / GRID_SIZE};
	if (grid_pos.x >= worldMap.width || grid_pos.y >= worldMap.height || grid_pos.x < 0 ||
		grid_pos.y < 0)
	{
		grid_pos.x = INVALID;
		grid_pos.y = INVALID;
	}
	return (grid_pos);
}

double degree_to_radians(double degree)
{
	return (degree * M_PI / 180.0);
}

double fix_angle(double angle)
{
	if (angle > 359)
		angle -= 360;
	if (angle < 0)
		angle += 360;
	return angle;
}

t_position get_grid_center(t_grid_position grid_pos)
{

	const t_position pos = {.x = (grid_pos.x + 1) * GRID_SIZE, .y = (grid_pos.y + 1) * GRID_SIZE};
	const double half_grid = GRID_SIZE / 2;
	const t_position center = {.x = pos.x - half_grid, .y = pos.y - half_grid};

	return (center);
}

t_bool is_valid_grid_position(t_map worldmap, t_grid_position position)
{
	return ((position.x > 0 && position.x < worldmap.width) &&
			(position.y > 0 && position.y < worldmap.height));
}