#ifndef RAYTRACER_H
#define RAYTRACER_H
#include <defs.h>

t_bool is_facing_north(double angle);
t_bool is_facing_south(double angle);
t_bool is_facing_east(double angle);
t_bool is_facing_west(double angle);
t_grid_position to_grid_position(t_map worldMap, t_position pos);
int min_i(int a, int b);
int max_i(int a, int b);
double min_d(double a, double b);
double max_d(double a, double b);
t_bool hit_obstacle(t_map worldMap, t_position pos);
t_position find_horizontal_line(t_data *data, double ray_angle);
t_position find_vertical_line(t_data *data, double ray_angle);
void run();

#endif