#include <libft.h>
#include <parser/texture_parser.h>
#include <parser/utils_parser.h>
#include <stdio.h>

static t_texture_enum texture_to_enum(char *texture_type)
{
	if(ft_strncmp("NO", texture_type, 2) == 0)
		return (NO);
	else if(ft_strncmp("SO", texture_type, 2) == 0)
		return (SO);
	else if(ft_strncmp("WE", texture_type, 2) == 0)
		return (WE);
	else if(ft_strncmp("EA", texture_type, 2) == 0)
		return (EA);
	else
		return (SP);
}

static t_bool is_valid_color_range(unsigned char *colors)
{
	int i = 0;
	while(i < 3)
	{
		if(colors[i] < 0 || colors[i] > 255)
			return (FALSE);
		++i;
	}
	return (TRUE);
}

t_bool is_texture(const char *line)
{
	if(ft_strncmp("NO", line, 2) == 0)
		return (TRUE);
	else if(ft_strncmp("SO", line, 2) == 0)
		return (TRUE);
	else if(ft_strncmp("WE", line, 2) == 0)
		return (TRUE);
	else if(ft_strncmp("EA", line, 2) == 0)
		return (TRUE);
	else if(ft_strncmp("S", line, 1) == 0)
		return (TRUE);
	return (FALSE);
}

t_status get_texture(const char *line, t_texture textures[])
{
	char **split = NULL;
	t_texture_enum text_index;
	t_status ret = TEXTURE_INFO_ERROR;

	split = ft_split(line, ' ');
	if(!split)
		return (MALLOC_ERROR);
	text_index = texture_to_enum(split[0]);
	if(num_of_strings(split) == 2 && text_index != INVALID_TEXTURE)
	{
		ft_strcpy(&(textures[text_index].filename[0]), split[1]);
		ret = SUCCESS;
	}
	free_split(split);
	return (ret);
}

t_status get_color(const char *line, t_color *color)
{
	unsigned char *address = (unsigned char *)color;
	char **split = NULL;
	t_status ret = SUCCESS;

	split = ft_split(&line[1], ',');
	if(!split)
		return (MALLOC_ERROR);
	if(num_of_strings(split) == 3)
	{
		address[0] = ft_atoi(split[2]);
		address[1] = ft_atoi(split[1]);
		address[2] = ft_atoi(split[0]);
		address[3] = 0xff;
	}
	if(!is_valid_color_range(address))
		ret = COLOR_ERROR;
	free_split(split);
	return (ret);
}