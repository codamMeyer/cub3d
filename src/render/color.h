#ifndef COLOR_H
#define COLOR_H
#include <utils/defs.h>
#include <utils/utils.h>

t_color_rgba get_black_color();
t_color_rgba get_pixel_color(const t_texture *texture, int x, int y);
t_bool is_black(t_color_rgba color);
t_color_rgba apply_shading(double distance, t_color_rgba color, double min_dist);
t_color_rgba apply_floor_shading(double distance, t_color_rgba color, double min_dist);
t_texture_position get_wall_texture_position(const t_texture *texture,
											 const t_ray *ray,
											 t_dimensions wall_dimensions,
											 int wall_index);

#endif