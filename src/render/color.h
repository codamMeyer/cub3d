#ifndef COLOR_H
#define COLOR_H
#include <utils/position.h>

typedef struct s_color_rgba
{
	uint8_t blue;
	uint8_t green;
	uint8_t red;
	uint8_t opacity;
} t_color_rgba;

t_color_rgba get_black_color(void);
t_bool is_black(t_color_rgba color);
t_color_rgba get_pixel_color(const t_texture *texture, int x, int y);
t_color_rgba apply_shading(double distance, t_color_rgba color, double min_dist);
t_color_rgba apply_floor_shading(double distance, t_color_rgba color, double min_dist);
t_color_rgba apply_ceiling_shading(double distance, t_color_rgba color, double min_dist);
t_texture_position get_wall_texture_position(const t_texture *texture,
											 const t_ray *ray,
											 t_dimensions wall_dimensions,
											 int wall_index);
#endif