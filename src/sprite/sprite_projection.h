#ifndef SPRITE_PROJECTION_H
# define SPRITE_PROJECTION_H
# include "sprite.h"
# include <game/game.h>
# include <player/player.h>
# include <utils/defs.h>
# include <raycast/raycast_utils.h>

void				get_sprite_projection(t_player player, \
											t_window screen, \
											t_sprite *sprite);
t_bool				in_sprites_list(t_sprite *sprites, \
									t_position center, \
									int index);
void				swap(t_sprite *cur, t_sprite *prev);
void				sort(t_sprite *sprites, int sprite_count);
t_intersections		create_intersections(const t_player *player, double angle);

#endif