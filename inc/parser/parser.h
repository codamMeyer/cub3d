#ifndef PARSER_H
#define PARSER_H
#include <utils/defs.h>

t_status get_resolution(const char *line, t_window *window);
t_status parse_input(const char *filename, t_data *data);
t_status check_file_extension(const char *filename);

#endif