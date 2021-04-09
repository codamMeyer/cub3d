#ifndef RAY_CASTING_LOGIC_H
#define RAY_CASTING_LOGIC_H
#include <player/player.h>
#include <utils/defs.h>

t_bool is_left_or_right(double ray_angle);
double get_y_increment_for_horizontal_detection(double ray_angle);
double get_x_increment_for_horizontal_detection(double ray_angle, double tan_angle);
t_position find_wall(t_map worldMap, double x_increment, double y_increment, t_position ray);
double get_x_increment_for_vertical_detection(double ray_angle);
double get_y_increment_for_vertical_detection(double ray_angle, double tan_angle);
t_bool is_up_or_down(double ray_angle);
t_position get_first_vertical_intersection(t_player player, double ray_angle, double tan_angle);
t_position get_first_horizontal_intersection(t_player player, double ray_angle, double tan_angle);

#endif