#ifndef GRID_POSITION_H
# define GRID_POSITION_H
# include "map_utils.h"
# include "position.h"

typedef struct s_grid_position
{
	int	x;
	int	y;
}	t_grid_position;

t_grid_position	to_grid_position(t_map worldMap, t_position pos);
t_position		get_grid_center(t_grid_position grid_pos);
t_bool			is_valid_grid_position(t_map worldmap, t_grid_position pos);
t_bool			is_valid_position(t_map worldmap, t_position pos);
t_position		compute_grid_center(t_map worldMap, t_position pos);

#endif