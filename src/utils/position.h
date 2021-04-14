#ifndef POSITION_H
# define POSITION_H
# include "defs.h"

typedef struct s_position
{
	double	x;
	double	y;
}	t_position;

typedef struct s_texture_position
{
	int	x;
	int	y;
}	t_texture_position;

typedef struct s_ray
{
	t_position		pos;
	double			distance;
	double			angle;
	t_orientation	orientation;
}	t_ray;

t_position		create_invalid_position(void);
double			get_distance_from_player(t_position ray_coord, \
											t_position player_coord);
t_bool			is_same_pos(t_position pos1, t_position pos2);

#endif