#ifndef PLAYER_H
# define PLAYER_H
# include <utils/position.h>

typedef struct s_player
{
	t_position	position;
	int			FOV;
	double		angle;
	int			speed;
	double		dist_to_plane;
}	t_player;

t_player	create_player(void);
t_bool		move_left(t_player *player, t_map worldMap);
t_bool		move_right(t_player *player, t_map worldMap);
t_bool		move_forward(t_player *player, t_map worldMap);
t_bool		move_backward(t_player *player, t_map worldMap);
void		turn_counterclockwise(t_player *player);
void		turn_clockwise(t_player *player);

#endif