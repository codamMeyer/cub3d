#ifndef MAP_PARSER_UTILS_H
# define MAP_PARSER_UTILS_H
# include <player/player.h>
# include <utils/defs.h>
# include <utils/grid_position.h>

t_bool	is_player_initialized(t_map *map, \
								t_player *player, \
								t_grid_position pos);
void	fill_spaces(t_map *map, int i, int j, int line_len);
int		get_value(char c, char **line, int j, int *sprite_count);

#endif