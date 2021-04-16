#ifndef UTILS_PARSER_H
# define UTILS_PARSER_H
# include <utils/defs.h>

t_bool	is_valid_hex_color(char *color);
int		num_of_strings(char **split);
void	free_split(char **split);
t_bool	is_wall(char **line, int i);
t_bool	is_map(const char *line);

#endif