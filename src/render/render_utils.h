#ifndef RENDER_UTILS_H
#define RENDER_UTILS_H
#include <game/game.h>
#include <player/player.h>

t_dimensions get_dimensions(double dist_to_wall, t_player player, t_window screen);

#endif