#include <libft.h>
#include <parser/texture_parser.h>
#include <parser/utils_parser.h>
#include <stdio.h>

static t_bool	is_valid_color_range(char **colors)
{
	const int	red = ft_atoi(colors[2]);
	const int	green = ft_atoi(colors[1]);
	const int	blue = ft_atoi(colors[0]);

	if (!is_valid_hex_color(colors[0]) || \
	!is_valid_hex_color(colors[1]) || \
	!is_valid_hex_color(colors[2]))
		return (FALSE);
	return ((red >= 0 && red <= 255) && \
			(green >= 0 && green <= 255) && \
			(blue >= 0 && blue <= 255));
}

t_texture_enum	texture_to_enum(char *texture_type)
{
	if (ft_strncmp("NO", texture_type, 2) == 0)
		return (NO);
	else if (ft_strncmp("SO", texture_type, 2) == 0)
		return (SO);
	else if (ft_strncmp("WE", texture_type, 2) == 0)
		return (WE);
	else if (ft_strncmp("EA", texture_type, 2) == 0)
		return (EA);
	else
		return (SP);
}

t_bool	is_texture(const char *line)
{
	if (ft_strncmp("NO", line, 2) == 0)
		return (TRUE);
	else if (ft_strncmp("SO", line, 2) == 0)
		return (TRUE);
	else if (ft_strncmp("WE", line, 2) == 0)
		return (TRUE);
	else if (ft_strncmp("EA", line, 2) == 0)
		return (TRUE);
	else if (ft_strncmp("S", line, 1) == 0)
		return (TRUE);
	return (FALSE);
}

t_status	get_texture(const char *line, t_texture textures[])
{
	char			**split;
	t_texture_enum	text_index;
	t_status		ret;

	split = NULL;
	ret = TEXTURE_INFO_ERROR;
	split = ft_split(line, ' ');
	if (!split)
		return (MALLOC_ERROR);
	text_index = texture_to_enum(split[0]);
	if (num_of_strings(split) == 2 && text_index != INVALID_TEXTURE)
	{
		ft_strcpy(&(textures[text_index].filename[0]), split[1]);
		ret = SUCCESS;
	}
	free_split(split);
	return (ret);
}

t_status	get_color(const char *line, t_color *color)
{
	char		**split;
	t_status	ret;

	ret = COLOR_ERROR;
	split = NULL;
	split = ft_split(&line[1], ',');
	if (!split)
		return (MALLOC_ERROR);
	if (num_of_strings(split) == 3 && is_valid_color_range(split) &&\
		!color->initialized)
	{
		color->red = ft_atoi(split[0]);
		color->green = ft_atoi(split[1]);
		color->blue = ft_atoi(split[2]);
		color->opacity = 0xFF;
		color->initialized = TRUE;
		ret = SUCCESS;
	}
	free_split(split);
	return (ret);
}
