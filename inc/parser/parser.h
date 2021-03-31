#ifndef PARSER_H
#define PARSER_H
#include <utils/defs.h>

t_status get_resolution(const char *line, t_window *window);
t_status check_file_extension(const char *filename);
t_status init_map_matrix(const int fd, t_map *map, t_player *player);
t_status parse_map(const int fd, t_map *map);
t_status parse_input(const char *filename, t_data *data);

#endif