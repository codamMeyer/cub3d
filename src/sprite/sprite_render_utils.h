#ifndef SPRITE_RENDER_UTILS_H
# define SPRITE_RENDER_UTILS_H
# include "sprite.h"
# include "sprite_render.h"

double				get_sprite_screen_center(double dist_to_plane, \
								double sprite_to_player_angle, \
								double player_angle, \
								double sprite_angle);
double				get_sprite_angle(t_player player, t_sprite sprite);
t_texture_position	get_texture_position(const t_texture *texture, \
												t_dimensions dimensions, \
												int y_index, \
												double x);
t_bool				is_visible(t_sprite_projection sprite, \
								int col, \
								double dist_to_wall);

#endif