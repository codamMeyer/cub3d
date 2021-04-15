#ifndef GAME_H
# define GAME_H
# include <utils/defs.h>
# include <render/color.h>
# include <sprite/sprite.h>
# include <player/player.h>
 
typedef struct s_window
{
	int	width;
	int	height;
}	t_window;

typedef struct s_data
{
	t_window		screen;
	t_img			img;
	t_map			worldMap;
	int				visible_sprites;
	t_sprite		*sprites;
	t_player		player;
	t_texture		textures[6];
	t_color			floor;
	t_color			ceiling;
	t_bool			save;
}	t_data;

void	run(const char *filename, t_bool save);

#endif