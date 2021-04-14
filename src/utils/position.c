#include "position.h"
#include <math.h>

t_position	create_invalid_position(void)
{
	t_position	pos;

	pos.x = INVALID;
	pos.y = INVALID;
	return (pos);
}

double	get_distance_from_player(t_position ray_coord, t_position player_coord)
{
	const double	x_diff = (player_coord.x - ray_coord.x) \
								* (player_coord.x - ray_coord.x);
	const double	y_diff = (player_coord.y - ray_coord.y) \
								* (player_coord.y - ray_coord.y);

	return (sqrt(x_diff + y_diff));
}

t_bool	is_same_pos(t_position pos1, t_position pos2)
{
	return ((pos1.x == pos2.x) && (pos1.y == pos2.y));
}
