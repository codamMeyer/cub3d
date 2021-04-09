#include "color.h"
#include <math.h>
#include <utils/math_utils.h>

t_color_rgba get_black_color()
{
	const t_color_rgba black = {.red = 0, .green = 0, .blue = 0, .opacity = 0xFF};

	return (black);
}

t_color_rgba get_pixel_color(const t_texture *texture, int x, int y)
{
	const int bytes_per_pixel = 4;
	const int index = (x + y * texture->width) * bytes_per_pixel;
	t_color_rgba color;

	color = get_black_color();
	if (x >= texture->width || y >= texture->height)
		return (color);
	if (x < 0 || y < 0)
		return (color);
	color.red = texture->data[index + 2];
	color.green = texture->data[index + 1];
	color.blue = texture->data[index];
	color.opacity = texture->data[index + 3];
	return (color);
}

t_bool is_black(t_color_rgba color)
{
	return (color.red == 0 && color.green == 0 && color.blue == 0 && color.opacity == 0xFF);
}

t_color_rgba apply_shading(double distance, t_color_rgba color, double min_dist)
{
	const double gradient = 1.0 - ((distance - min_dist) / 1000);
	t_color_rgba shade;

	if (distance <= min_dist || is_black(color))
		return (color);
	shade.red = max_i(0, color.red * gradient);
	shade.green = max_i(0, color.green * gradient);
	shade.blue = max_i(0, color.blue * gradient);
	return (shade);
}

t_color_rgba apply_floor_shading(double distance, t_color_rgba color, double min_dist)
{
	const double gradient = 1.0 - ((distance - min_dist) / 100);
	t_color_rgba shade;

	if (distance >= min_dist || is_black(color))
		return (color);
	shade.red = max_i(0, color.red / gradient);
	shade.green = max_i(0, color.green / gradient);
	shade.blue = max_i(0, color.blue / gradient);
	return (shade);
}

t_texture_position get_wall_texture_position(const t_texture *texture,
											 const t_ray *ray,
											 t_dimensions wall_dimensions,
											 int wall_index)
{
	const double texture_to_wall_ratio =
		(double)texture->height / (double)wall_dimensions.real_height;

	const int wall_pixel_position = (wall_index - wall_dimensions.real_top);
	t_texture_position pos;

	pos.y = floor(wall_pixel_position * texture_to_wall_ratio);

	if (ray->orientation == HORIZONTAL)
		pos.x = (int)ray->pos.x % texture->width;
	else
		pos.x = (int)ray->pos.y % texture->width;
	return (pos);
}