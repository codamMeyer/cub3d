#ifndef VERTICAL_DETECTION_H
# define VERTICAL_DETECTION_H
# include <player/player.h>
# include <utils/defs.h>

t_position	get_increment_for_vertical_detection(double ray_angle, \
												double tan_angle);
t_position	get_first_vertical_intersection(t_player player, \
											double ray_angle, \
											double tan_angle);

#endif