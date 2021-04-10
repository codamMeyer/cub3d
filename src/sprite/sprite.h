#ifndef SPRITE_H
#define SPRITE_H
#include <game/game.h>
#include <libft.h>
#include <player/player.h>
#include <utils/defs.h>

typedef struct s_sprite
{
	t_position center;
} t_sprite;

typedef struct s_sprite_projection
{
	t_position start;
	t_position end;
	double dist_from_player;
	t_dimensions dimensions;
} t_sprite_projection;

void find_sprites(t_player player, t_map worldMap, t_list **sprites, double ray_angle);
t_sprite_projection create_sprite_projection(t_player player, t_window screen, t_sprite sprite);
void draw_sprites_slice(t_data *data, int col, double dist_to_wall, t_sprite_projection sprite);

#endif