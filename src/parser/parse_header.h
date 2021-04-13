#ifndef PARSE_HEADER_H
# define PARSE_HEADER_H
# include <errors/errors.h>
# include <game/game.h>

t_status	get_header_information(const char *filename, t_data *data);
t_status	get_resolution(const char *line, t_window *window);
t_status	check_file_extension(const char *filename);

#endif