#include "shade.h"
#include "color.h"
#include <utils/math_utils.h>

static t_color	get_lighter_color(t_color color, double gradient)
{
	const t_color	darker_color = {
		.red = min_i(255, color.red / gradient),
		.green = min_i(255, color.green / gradient),
		.blue = min_i(255, color.blue / gradient),
		.opacity = 0xFF,
	};

	return (darker_color);
}

t_color	get_darker_color(t_color color, double gradient)
{
	const t_color	darker_color = {
		.red = max_i(0, color.red * gradient),
		.green = max_i(0, color.green * gradient),
		.blue = max_i(0, color.blue * gradient),
		.opacity = 0xFF,
	};

	return (darker_color);
}

t_color	apply_shading(double distance, t_color color, double min_dist)
{
	const double	grad = max_d(0.3, 1.0 - ((distance - min_dist) / 1000));
	t_color			new_color;

	if (distance <= min_dist || is_black(color))
		return (color);
	new_color = get_darker_color(color, grad);
	return (new_color);
}

t_color	apply_ceiling_shading(double distance,
									t_color color,
									double min_dist)
{
	const double	grad = 1.0 - ((distance - min_dist) / 100);
	t_color			new_color;

	if (distance <= min_dist || is_black(color))
		return (color);
	new_color = get_darker_color(color, grad);
	return (new_color);
}

t_color	apply_floor_shading(double distance,
							t_color color,
							double min_dist)
{
	const double	grad = 1.0 - ((distance - min_dist) / 100);
	t_color			new_color;

	if (distance >= min_dist || is_black(color))
		return (color);
	new_color = get_lighter_color(color, grad);
	return (new_color);
}
