#ifndef MAP_PARSER_H
#define MAP_PARSER_H
#include <utils/defs.h>

t_bool check_map_content(t_map *map, t_player *player);
t_status populate_map(const int fd, t_map *map, char **line);
t_status get_map_dimentions(const int fd, char **line, t_map *map);

#endif