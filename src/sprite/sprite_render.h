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
											t_sprite_projection sprite);
void					find_and_draw_sprites(int col, \
												t_data *data, \
												t_ray *ray, \
												double wall_dist, int sprite_count, t_sprite_projection *sprites);
t_sprite_projection		create_sprite_projection(t_player player, \
													t_window screen, \
													t_sprite sprite);
void get_all_sprites(t_data *data, t_sprite_projection *sprites, int *index, double angle);
void					get_sprite_projection(t_player player,
											t_window screen,
											t_sprite_projection *sprite);

#endif