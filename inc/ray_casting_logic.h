#ifndef RAY_CASTING_LOGIC_H
#define RAY_CASTING_LOGIC_H
#include <defs.h>

t_position find_vertical_line(t_data *data, double ray_angle);
t_position find_horizontal_line(t_data *data, double ray_angle);
double find_closer_wall(t_position h_intersection,
						t_position v_intersection,
						t_player player,
						double ray_angle);
double get_wall_distance(t_position ray_coord, t_position player_coord);
#endif