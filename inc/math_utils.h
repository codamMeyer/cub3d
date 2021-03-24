#ifndef MATH_UTILS_H
#define MATH_UTILS_H
#include <defs.h>
#include <map.h>

int min_i(int a, int b);
int max_i(int a, int b);
double min_d(double a, double b);
double max_d(double a, double b);
t_grid_position to_grid_position(t_map worldMap, t_position pos);
double degree_to_radians(double degree);
double abs_value(double value);
double fix_angle(double angle);
t_position get_grid_center(t_grid_position grid_pos);
t_position get_grid_center_offset(t_grid_position grid_pos);
t_bool is_valid_grid_position(t_map worldmap, t_grid_position position);

#endif