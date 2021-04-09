#include "raycast_utils2.h"
#include <math.h>

t_position create_invalid_position()
{
	t_position pos;

	pos.x = INVALID;
	pos.y = INVALID;
	return (pos);
}

double get_distance_from_player(t_position ray_coord, t_position player_coord)
{
	const double x_diff = (player_coord.x - ray_coord.x) * (player_coord.x - ray_coord.x);
	const double y_diff = (player_coord.y - ray_coord.y) * (player_coord.y - ray_coord.y);
	return (sqrt(x_diff + y_diff));
}
