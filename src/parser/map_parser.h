#ifndef MAP_PARSER_H
#define MAP_PARSER_H
#include <errors/errors.h>
#include <utils/defs.h>
#include <player/player.h>

t_status check_map_content(t_map *map, t_player *player);
t_status populate_map(const int fd, t_map *map, char **line);
t_status get_map_dimensions(const int fd, char **line, t_map *map);

#endif