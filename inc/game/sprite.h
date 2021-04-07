#ifndef SPRITE_H
#define SPRITE_H
#include <utils/defs.h>

typedef struct s_sprite
{
	t_position center;
	t_grid_position grid_pos;
	int height;
	int width;
	int start_y;
	int end_y;
	int start_x;
	int end_x;
	double dist_to_sprite;
	t_dimensions dimensions;
} t_sprite;

t_sprite find_sprites(t_data *data, double ray_angle);
t_sprite find_sprite_vertical_line(t_data *data, double ray_angle);
t_sprite find_sprite_horizontal_line(t_data *data, double ray_angle);
void draw_sprites(t_data *data, t_sprite *sprites, int size);
void get_sprite_values(t_data *data, t_sprite *sprite);
void draw_sprites_vertical_line(t_data *data, int col, double dist_to_wall, t_sprite sprite);

#endif