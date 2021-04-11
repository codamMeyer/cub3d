#ifndef WALLS_H
#define WALLS_H
#include <game/game.h>
#include <utils/defs.h>

double find_and_draw_walls(int col, t_data *data, t_ray *ray);
t_position find_wall_horizontal_line(t_data *data, double ray_angle);
t_position find_wall_vertical_line(t_data *data, double ray_angle);

#endif