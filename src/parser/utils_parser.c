#include "texture_parser.h"
#include "utils_parser.h"
#include <libft.h>
#include <stdio.h>
#include <stdlib.h>

t_bool	is_valid_hex_color(char *color)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = ft_strtrim(color, " ,");
	while (tmp[i] != '\0')
	{
		if (!ft_isdigit(tmp[i]))
		{
			free(tmp);
			return (FALSE);
		}
		++i;
	}
	free(tmp);
	return (TRUE);
}

int	num_of_strings(char **split)
{
	int	i;

	i = 0;
	if (split == NULL)
		return (i);
	while (split[i] != NULL)
		++i;
	return (i);
}

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i] != NULL)
	{
		free(split[i]);
		++i;
	}
	free(split);
}

t_bool	is_wall(char **line, int i)
{
	const int	line_len = ft_strlen(*line);
	const char	cur_char = (*line)[i];

	return (line_len > 1 && (cur_char == ' ' || cur_char == '1'));
}

t_bool	is_map(const char *line)
{
	return (line[0] != '\0' && \
			line[0] != 'R' && \
			line[0] != 'F' && \
			line[0] != 'C' && \
			!is_texture(line));
}
