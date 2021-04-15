#ifndef SPRITE_H
# define SPRITE_H
# include <player/player.h>
# include <utils/defs.h>

typedef struct s_sprite
{
	t_position		center;
	double			dist_from_player;
	t_position		start;
	t_position		end;
	t_dimensions	dimensions;
}	t_sprite;

// void get_all_sprites(t_data *data);
// int		find_sprites(t_player player, \
// 					t_map worldMap, \
// 					t_sprite *sprites, \
// 					double ray_angle);
// void	sort_sprites(t_sprite *sprites, int sprite_count);

#endif