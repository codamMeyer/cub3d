#ifndef SPRITE_H
#define SPRITE_H
#include <game/game.h>
#include <libft.h>
#include <player/player.h>
#include <utils/defs.h>

typedef struct s_sprite
{
	t_position center;
	int height;
	int width;
	int start_y;
	int end_y;
	int start_x;
	int end_x;
	double dist_to_sprite;
	t_dimensions dimensions;
} t_sprite;

void find_sprites(t_player player, t_map worldMap, t_list **sprites, double ray_angle);
void get_sprite_values(t_player player, t_window screen, t_sprite *sprite);
void draw_sprites_slice(t_data *data, int col, double dist_to_wall, t_sprite sprite);

#endif