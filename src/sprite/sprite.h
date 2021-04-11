#ifndef SPRITE_H
#define SPRITE_H
#include <libft.h>
#include <player/player.h>
#include <utils/defs.h>

typedef struct s_sprite
{
	t_position center;
	double dist_from_player;
} t_sprite;

int find_sprites(t_player player, t_map worldMap, t_sprite *sprites, double ray_angle);
void sort_sprites(t_list *sprites);

#endif