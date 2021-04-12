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

typedef struct s_intersections
{
	t_position hor_increment;
	t_position ver_increment;
	t_position horizontal;
	t_position vertical;
} t_intersections;

int find_sprites(t_player player, t_map worldMap, t_sprite *sprites, double ray_angle);
void sort_sprites(t_sprite *sprites, int sprite_count);

#endif