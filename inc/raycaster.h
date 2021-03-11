#ifndef RAYTRACER_H
#define RAYTRACER_H
#include <defs.h>

t_position find_horizontal_line(t_data *data, double ray_angle);
t_position find_vertical_line(t_data *data, double ray_angle);
void run();

#endif