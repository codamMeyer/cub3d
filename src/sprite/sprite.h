#ifndef SPRITE_H
# define SPRITE_H
# include <utils/defs.h>
# include <utils/position.h>

typedef struct s_sprite
{
	t_position		center;
	double			dist_from_player;
	t_position		start;
	t_position		end;
	t_dimensions	dimensions;
}	t_sprite;

#endif