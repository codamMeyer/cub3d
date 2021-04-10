#ifndef HORIZONTAL_DETECTION_H
#define HORIZONTAL_DETECTION_H
#include <player/player.h>
#include <utils/defs.h>

t_position get_first_horizontal_intersection(t_player player, double ray_angle, double tan_angle);
t_position get_increment_for_horizontal_detection(double ray_angle, double tan_angle);

#endif