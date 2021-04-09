#ifndef POSITION_H
#define POSITION_H
#include "defs.h"

typedef struct s_position
{
	double x;
	double y;
} t_position;

typedef struct s_grid_position
{
	int x;
	int y;
} t_grid_position;

typedef struct s_texture_position
{
	int x;
	int y;
} t_texture_position;

typedef struct s_ray
{
	t_position pos;
	double distance;
	double angle;
	t_orientation orientation;
} t_ray;

t_grid_position to_grid_position(t_map worldMap, t_position pos);
t_position get_grid_center(t_grid_position grid_pos);
t_bool is_valid_grid_position(t_map worldmap, t_grid_position position);
t_position create_invalid_position();
double get_distance_from_player(t_position ray_coord, t_position player_coord);


#endif