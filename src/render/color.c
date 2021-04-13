#include "color.h"
#include <math.h>
#include <utils/math_utils.h>

t_color	get_black_color(void)
{
	const t_color	black = {
								.red = 0,
								.green = 0,
								.blue = 0,
								.opacity = 0xFF
							};

	return (black);
}

t_bool	is_black(t_color color)
{
	return (color.red == 0 && \
			color.green == 0 && \
			color.blue == 0 && \
			color.opacity == 0xFF);
}

t_color	get_pixel_color(const t_texture *texture, int x, int y)
{
	const int	bytes_per_pixel = 4;
	const int	index = (x + y * texture->width) * bytes_per_pixel;
	t_color		color;

	color = get_black_color();
	if (x >= texture->width || y >= texture->height)
		return (color);
	if (x < 0 || y < 0)
		return (color);
	color.opacity = texture->data[index + 3];
	color.red = texture->data[index + 2];
	color.green = texture->data[index + 1];
	color.blue = texture->data[index];
	return (color);
}

t_texture_position	get_wall_texture_position(const t_texture *texture,
											 const t_ray *ray,
											 t_dimensions wall_dimensions,
											 int wall_index)
{
	const double		texture_to_wall_ratio = (double)texture->height / \
										(double)wall_dimensions.real_height;
	const int			wall_pixel_position = \
									(wall_index - wall_dimensions.real_top);
	t_texture_position	pos;

	pos.y = floor(wall_pixel_position * texture_to_wall_ratio);
	if (ray->orientation == HORIZONTAL)
		pos.x = (int)ray->pos.x % texture->width;
	else
		pos.x = (int)ray->pos.y % texture->width;
	return (pos);
}
