#ifndef RENDER_H
#define RENDER_H
#include <defs.h>

void draw_slice(t_data *data, int slice_col, t_ray *ray);
t_color get_pixel_color(const t_texture *texture, int x, int y);
#endif