#ifndef MATH_UTILS2_H
#define MATH_UTILS2_H
#include <utils/defs.h>

t_grid_position to_grid_position(t_map worldMap, t_position pos);
double degree_to_radians(double degree);
double fix_angle(double angle);
t_position get_grid_center(t_grid_position grid_pos);
t_bool is_valid_grid_position(t_map worldmap, t_grid_position position);

#endif