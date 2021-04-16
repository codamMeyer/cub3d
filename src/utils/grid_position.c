#include "grid_position.h"

t_grid_position	to_grid_position(t_map worldMap, t_position pos)
{
	t_grid_position	grid_pos;

	grid_pos.x = pos.x / GRID_SIZE;
	grid_pos.y = pos.y / GRID_SIZE;
	if (grid_pos.x >= worldMap.width - 1 || \
		grid_pos.y >= worldMap.height - 1 || \
		grid_pos.x < 0 || grid_pos.y < 0)
	{
		grid_pos.x = INVALID;
		grid_pos.y = INVALID;
	}
	return (grid_pos);
}

t_position	get_grid_center(t_grid_position grid_pos)
{
	const t_position	pos = {
								.x = (grid_pos.x + 1) * GRID_SIZE,
								.y = (grid_pos.y + 1) * GRID_SIZE
							};
	const double		half_grid = GRID_SIZE / 2;
	const t_position	center = {
									.x = pos.x - half_grid,
									.y = pos.y - half_grid
								};

	return (center);
}

t_position	compute_grid_center(t_map worldMap, t_position pos)
{
	const t_grid_position	grid_pos = to_grid_position(worldMap, pos);
	const double			half_grid = GRID_SIZE / 2;
	t_position				center;

	pos.x = (grid_pos.x + 1) * GRID_SIZE;
	pos.y = (grid_pos.y + 1) * GRID_SIZE;
	center.x = pos.x - half_grid;
	center.y = pos.y - half_grid;
	return (center);
}

t_bool	is_valid_grid_position(t_map worldmap, t_grid_position pos)
{
	return ((pos.x > 0 && pos.x < worldmap.width) && \
			(pos.y > 0 && pos.y < worldmap.height));
}

t_bool	is_valid_position(t_map worldmap, t_position pos)
{
	return (is_valid_grid_position(worldmap, \
			to_grid_position(worldmap, pos)));
}
