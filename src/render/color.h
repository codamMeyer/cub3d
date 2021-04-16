#ifndef COLOR_H
# define COLOR_H
# include <utils/position.h>

typedef struct s_color_rgba
{
	uint8_t	blue;
	uint8_t	green;
	uint8_t	red;
	uint8_t	opacity;
	t_bool	initialized;
}	t_color;

t_color				get_black_color(void);
t_bool				is_black(t_color color);
t_color				get_pixel_color(const t_texture *texture, int x, int y);
t_texture_position	get_wall_texture_position(const t_texture *texture, \
											 const t_ray *ray, \
											 t_dimensions wall_dimensions, \
											 int wall_index);

#endif