#ifndef SPRITE_H
#define SPRITE_H
#include <utils/defs.h>

typedef struct s_sprite
{
	t_position center;
	t_grid_position grid_pos;
} t_sprite;

t_sprite find_sprites(t_data *data, double ray_angle);
t_sprite find_sprite_vertical_line(t_data *data, double ray_angle);
t_sprite find_sprite_horizontal_line(t_data *data, double ray_angle);
void draw_sprites(t_data *data, t_sprite *sprites, int size);

#endif