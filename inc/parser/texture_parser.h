#ifndef PARSER_TEXTURE_H
#define PARSER_TEXTURE_H
#include <utils/defs.h>

t_status get_texture(const char *line, t_texture textures[]);
t_bool is_texture(const char *line);
t_status get_color(const char *line, t_color *color);

#endif