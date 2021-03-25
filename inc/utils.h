#ifndef UTILS_H
#define UTILS_H
#include "defs.h"



void my_mlx_pixel_put(t_img *data, int x, int y, t_color color);
int paint_background(int w, int h, t_data *data);
void draw_square(t_img *img, int size, int start_x, int start_y, int color);

#endif
