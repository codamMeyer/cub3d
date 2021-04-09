#ifndef RAY_CASTING_LOGIC_H
#define RAY_CASTING_LOGIC_H
#include <player/player.h>
#include <utils/defs.h>

double get_y_increment_for_horizontal_detection(double ray_angle);
double get_x_increment_for_horizontal_detection(double ray_angle, double tan_angle);
double get_x_increment_for_vertical_detection(double ray_angle);
double get_y_increment_for_vertical_detection(double ray_angle, double tan_angle);
t_position get_first_vertical_intersection(t_player player, double ray_angle, double tan_angle);
t_position get_first_horizontal_intersection(t_player player, double ray_angle, double tan_angle);

#endif