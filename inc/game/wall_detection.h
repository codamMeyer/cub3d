#ifndef WALL_DETECTION_H
#define WALL_DETECTION_H
#include <utils/defs.h>

double get_distance_from_player(t_position ray_coord, t_position player_coord);
t_position find_wall_vertical_line(t_data *data, double ray_angle);
t_position find_wall_horizontal_line(t_data *data, double ray_angle);
void find_closest_wall(t_position h_intersection,
					   t_position v_intersection,
					   t_player player,
					   t_ray *ray);
double find_and_draw_walls(int col, t_data *data, t_ray *ray);
#endif