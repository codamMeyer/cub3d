#ifndef SPRITE_RENDER_H
# define SPRITE_RENDER_H
# include "sprite.h"
# include <game/game.h>

typedef struct s_sprite_projection
{
	t_position		center;
	t_position		start;
	t_position		end;
	double			dist_from_player;
	t_dimensions	dimensions;
}	t_sprite_projection;

void					draw_sprites_slice(t_data *data, \
											int col, \
											double dist_to_wall, \
											t_sprite sprite);
void					draw_sprites(t_data *data, \
									int col, \
									t_ray *ray, \
									double wall_dist);
void					find_sprites(t_data *data, int *index, double angle);
void					get_sprite_projection(t_player player,
												t_window screen,
												t_sprite *sprite);
void					sort(t_sprite *sprites, int sprite_count);
int						get_all_sprites(t_data *data);
#endif