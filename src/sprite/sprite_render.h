#ifndef SPRITE_RENDER_H
# define SPRITE_RENDER_H
# include "sprite.h"
# include <game/game.h>

void					draw_sprites(t_data *data, int col, double wall_dist);
void					get_all_sprites(t_data *data);

#endif