#include "render_utils.h"
#include <math.h>
#include <utils/map_utils.h>
#include <utils/math_utils.h>

t_dimensions	get_dimensions(double dist_to_wall,
								t_player player,
								t_window screen)
{
	t_dimensions	dim;

	dim.real_height = round((GRID_SIZE / dist_to_wall) * player.dist_to_plane);
	dim.real_width = round((GRID_SIZE / dist_to_wall) * player.dist_to_plane);
	dim.height = min_i(dim.real_height, screen.height);
	dim.width = min_i(dim.real_width, screen.width);
	dim.top = round(((double)screen.height / 2.0) - (dim.height / 2.0));
	dim.real_top = round(((double)screen.height / 2.0) \
							- (dim.real_height / 2.0));
	dim.bottom = dim.top + dim.height;
	return (dim);
}

void	my_mlx_pixel_put(t_img *img, int x, int y, t_color color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	dst[0] = color.blue;
	dst[1] = color.green;
	dst[2] = color.red;
	dst[3] = color.opacity;
}
