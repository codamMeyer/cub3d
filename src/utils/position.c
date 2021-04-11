#include "position.h"
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

t_bool is_valid_position(t_map worldmap, t_position position)
{
	return (is_valid_grid_position(worldmap, to_grid_position(worldmap, position)));
}

t_position create_invalid_position()
{
	t_position pos;

	pos.x = INVALID;
	pos.y = INVALID;
	return (pos);
}

double get_distance_from_player(t_position ray_coord, t_position player_coord)
{
	const double x_diff = (player_coord.x - ray_coord.x) * (player_coord.x - ray_coord.x);
	const double y_diff = (player_coord.y - ray_coord.y) * (player_coord.y - ray_coord.y);
	return (sqrt(x_diff + y_diff));
}

t_bool is_same_pos(t_position pos1, t_position pos2)
{
	return ((pos1.x == pos2.x) && (pos1.y == pos2.y));
}