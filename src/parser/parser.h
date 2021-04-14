#ifndef PARSER_H
# define PARSER_H
# include <errors/errors.h>
# include <game/game.h>
# include <player/player.h>
# include <utils/defs.h>

t_status	init_map_matrix(const char *filename, t_map *map, t_player *player);
t_status	parse_map(const char *filename, t_map *map);
t_status	parse_input(const char *filename, t_data *data);

#endif