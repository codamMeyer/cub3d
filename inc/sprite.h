#ifndef SPRITE_H
#define SPRITE_H
#include <defs.h>

typedef struct s_sprite
{
	t_position center;
	t_grid_position grid_pos;
} t_sprite;

void find_sprites(t_data *data, double ray_angle);
t_sprite find_sprite_vertical_line(t_data *data, double ray_angle);
t_sprite find_sprite_horizontal_line(t_data *data, double ray_angle);
#endif