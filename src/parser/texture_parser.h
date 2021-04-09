#ifndef PARSER_TEXTURE_H
#define PARSER_TEXTURE_H
#include <errors/errors.h>
#include <utils/defs.h>

t_texture_enum texture_to_enum(char *texture_type);
t_bool is_texture(const char *line);
t_status get_texture(const char *line, t_texture textures[]);
t_status get_color(const char *line, t_color_rgba *color);

#endif