#ifndef RAY_CASTING_LOGIC_H
#define RAY_CASTING_LOGIC_H
#include <defs.h>

t_position find_wall_vertical_line(t_data *data, double ray_angle);
t_position find_wall_horizontal_line(t_data *data, double ray_angle);
t_position find_sprite_horizontal_line(t_data *data, double ray_angle);
t_position find_sprite_vertical_line(t_data *data, double ray_angle);
#endif