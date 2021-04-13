#ifndef SHADE_H
# define SHADE_H
# include "color.h"

t_color	get_darker_color(t_color color, double gradient);
t_color	get_lighter_color(t_color color, double gradient);
t_color	apply_shading(double distance, t_color color, double min_dist);
t_color	apply_ceiling_shading(double distance, \
									t_color color, \
									double min_dist);
t_color	apply_floor_shading(double distance, \
							t_color color, \
							double min_dist);
#endif