#include <libft.h>
#include <parser/texture_parser.h>
#include <parser/utils_parser.h>
#include <stdio.h>
#include <stdlib.h>

int num_of_strings(char **split)
{
	int i = 0;
	if(split == NULL)
		return (i);
	while(split[i] != NULL)
		++i;
	return (i);
}

void free_split(char **split)
{
	int i = 0;
	while(split[i] != NULL)
	{
		free(split[i]);
		++i;
	}
	free(split);
}

t_bool is_wall(char **line, int i)
{
	const int line_len = ft_strlen(*line);
	const char cur_char = (*line)[i];

	return (line_len > 1 && (i >= line_len || cur_char == ' ' || cur_char == '1'));
}

t_bool is_sprite(char cur)
{
	return (cur == '2');
}

t_bool is_map(const char *line)
{
	return (line[0] != '\0' && line[0] != 'R' && line[0] != 'F' && line[0] != 'C' &&
			!is_texture(line));
}