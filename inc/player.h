#ifndef PLAYER_H
#define PLAYER_H
#include "defs.h"

int draw_player(t_data *data);
void init_player(t_data *data);
t_bool move_forward(t_player *player, t_data *data);
t_bool move_backward(t_player *player, t_data *data);
t_bool move_left(t_player *player, t_data *data);
t_bool move_right(t_player *player, t_data *data);
void turn_counterclockwise(t_player *player);
void turn_clockwise(t_player *player);

#endif