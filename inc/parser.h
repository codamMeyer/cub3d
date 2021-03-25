#ifndef PARSER_H
#define PARSER_H
#include <defs.h>

t_bool get_surface_color(const int fd, t_color *color_ptr, char identifier);
t_bool get_texture(const int fd, t_texture textures[]);
t_bool get_textures(const int fd, t_texture textures[]);
t_bool get_resolution(const int fd, t_window *window);
t_bool parse_imput(const char *filename);
t_texture_enum texture_to_enum(char *texture_type);

#endif