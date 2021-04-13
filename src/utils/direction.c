#include <utils/direction.h>

t_bool	is_facing_north(double angle)
{
	return (angle > 0 && angle < 180);
}

t_bool	is_facing_south(double angle)
{
	return (angle > 180 && angle < 360);
}

t_bool	is_facing_east(double angle)
{
	return ((angle < 90 && angle > 0) || (angle > 270 && angle < 360));
}

t_bool	is_facing_west(double angle)
{
	return (angle > 90 && angle < 270);
}
