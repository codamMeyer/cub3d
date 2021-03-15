#ifndef RAYTRACER_H
#define RAYTRACER_H
#include <defs.h>

t_position find_horizontal_line(t_data *data, double ray_angle);
t_position find_vertical_line(t_data *data, double ray_angle);
double get_wall_distance(t_position ray_coord, t_position player_coord);
void run();

#endif