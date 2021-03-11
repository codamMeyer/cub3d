#ifndef UTILS_H
#define UTILS_H
#include "defs.h"

void my_mlx_pixel_put(t_img *data, int x, int y, int color);
int paint_background(int w, int h, t_data *data);
void draw_square(t_img *img, int size, int start_x, int start_y, int color);
double degree_to_radians(double degree);
t_bool is_facing_north(double angle);
t_bool is_facing_south(double angle);
t_bool is_facing_east(double angle);
t_bool is_facing_west(double angle);


#endif
