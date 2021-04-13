#ifndef PLAYER_H
# define PLAYER_H
# include <utils/position.h>

typedef enum e_direction
{
	STILL = 0,
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
}	t_direction;

typedef enum e_rotation
{
	NONE = 0,
	CLOCKWISE = -1,
	COUNTERCLOCKWISE = 1,
}	t_rotation;

typedef struct s_player
{
	t_position	position;
	int			FOV;
	double		angle;
	int			speed;
	t_direction	direction;
	t_rotation	rotation;
	double		dist_to_plane;
}	t_player;

t_player	create_player(void);

#endif