#include "render_utils.h"
#include <math.h>
#include <utils/map_utils.h>
#include <utils/math_utils.h>

t_dimensions get_dimensions(double dist_to_wall, t_player player, t_window screen)
{

	t_dimensions dimensions;

	dimensions.real_height = round((GRID_SIZE / dist_to_wall) * player.dist_to_plane);
	dimensions.real_width = round((GRID_SIZE / dist_to_wall) * player.dist_to_plane);
	dimensions.height = min_i(dimensions.real_height, screen.height);
	dimensions.width = min_i(dimensions.real_width, screen.width);
	dimensions.top = round(((double)screen.height / 2.0) - (dimensions.height / 2.0));
	dimensions.real_top = round(((double)screen.height / 2.0) - (dimensions.real_height / 2.0));
	dimensions.bottom = dimensions.top + dimensions.height;

	return (dimensions);
}
