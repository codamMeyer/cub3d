#ifndef RAYCAST_UTILS_H
# define RAYCAST_UTILS_H
# include <utils/defs.h>
# include <utils/position.h>

typedef struct s_intersections
{
	t_position	hor_increment;
	t_position	ver_increment;
	t_position	horizontal;
	t_position	vertical;
}	t_intersections;

t_bool	is_straight_left_or_right(double ray_angle);
t_bool	is_straight_up_or_down(double ray_angle);
t_bool	detect_hit(t_map worldMap, t_position pos, t_collider collider);
double	fix_fisheye_effect(double dist, double angle);
void	apply_increment_to_intersections(t_intersections *intersections);

#endif