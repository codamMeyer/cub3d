#ifndef PARSER_H
#define PARSER_H
#include <defs.h>

t_bool get_color(const char *line, t_color *color_ptr);
t_bool get_texture(const char *line, t_texture textures[]);
t_bool get_resolution(const char *line, t_window *window);
t_bool parse_input(const char *filename,
				   t_window *window,
				   t_texture textures[],
				   t_color *floor,
				   t_color *ceiling);
t_texture_enum texture_to_enum(char *texture_type);

#endif