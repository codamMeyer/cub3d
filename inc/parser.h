#ifndef PARSER_H
#define PARSER_H
#include <defs.h>

t_status get_color(const char *line, t_color *color_ptr);
t_status get_texture(const char *line, t_texture textures[]);
t_status get_resolution(const char *line, t_window *window);
t_status parse_input(const char *filename, t_data *data);
t_texture_enum texture_to_enum(char *texture_type);
t_status check_file_extension(const char *filename);
t_status parse_map(const int fd, t_map *map);
t_status init_map_matrix(const int fd, t_map *map, t_player *player);
#endif