#ifndef RAYCAST_UTILS_H
#define RAYCAST_UTILS_H
#include <utils/defs.h>
#include <utils/position.h>

t_bool is_straight_left_or_right(double ray_angle);
t_bool is_straight_up_or_down(double ray_angle);
void keep_inside_map(t_grid_position *pos, t_map worldMap);
t_bool detect_hit(t_map worldMap, t_position pos, t_collider collider);
double fix_fisheye_effect(double dist, double ray_angle);

#endif