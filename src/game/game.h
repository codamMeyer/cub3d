#ifndef RAYTRACER_H
#define RAYTRACER_H
#include <errors/errors.h>
#include <player/player.h>
#include <render/color.h>
#include <utils/defs.h>
#include <sprite/sprite.h>

typedef struct s_window
{
	int width;
	int height;
} t_window;

typedef struct s_data
{
	t_window screen;
	t_img img;
	t_map worldMap;
	t_sprite *sprites;
	t_player player;
	t_texture textures[6];
	t_color_rgba floor;
	t_color_rgba ceiling;
	t_bool save;
} t_data;

void close_window(t_data *data);
t_status run(const char *filename, t_bool save);

#endif