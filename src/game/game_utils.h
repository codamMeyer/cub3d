#ifndef GAME_UTILS_H
# define GAME_UTILS_H
# include "game.h"

void		close_window(t_data *data, t_status status);
int			red_cross(t_data *data, t_status status);
t_texture	load_texture(t_data *data, char *filename);
t_status	load_textures(t_data *data);

#endif