#include <defs.h>
#include <get_next_line.h>
#include <libft/libft.h>
#include <parser.h>
#include <stdio.h>

static int num_of_strings(char **split)
{
	int i = 0;
	while(split[i] != NULL)
		++i;
	return (i);
}

static void free_split(char **split)
{
	int i = 0;
	while(split[i] != NULL)
	{
		free(split[i]);
		++i;
	}
	free(split);
}

static t_bool check_color_range(int colors[])
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

static t_bool get_color(const char *color_string, t_color *color)
{
	unsigned char *address = (unsigned char *)color;
	char **split = NULL;
	int colors[3];
	t_bool ret = TRUE;

	split = ft_split(color_string, ',');
	colors[0] = ft_atoi(split[2]);
	colors[1] = ft_atoi(split[1]);
	colors[2] = ft_atoi(split[0]);

	if(!check_color_range(colors))
		ret = FALSE;
	address[0] = colors[0];
	address[1] = colors[1];
	address[2] = colors[2];
	address[3] = 0xff;
	free_split(split);
	return (ret);
}

t_bool get_surface_color(const int fd, t_color *color_ptr, char identifier)
{
	char *line = NULL;
	char **split = NULL;
	t_bool ret = FALSE;

	if(get_next_line(fd, &line) && (line[0] == identifier))
	{
		split = ft_split(line, ' ');
		if(num_of_strings(split) == 2)
		{
			if(get_color(split[1], color_ptr))
				ret = TRUE;
		}
	}
	free_split(split);
	free(line);
	return (ret);
}

t_texture_enum texture_to_enum(char *texture_type)
{
	if(ft_strncmp("NO", texture_type, 2) == 0)
		return (NO);
	else if(ft_strncmp("SO", texture_type, 2) == 0)
		return (SO);
	else if(ft_strncmp("WE", texture_type, 2) == 0)
		return (WE);
	else if(ft_strncmp("EA", texture_type, 2) == 0)
		return (EA);
	else if(ft_strncmp("S", texture_type, 1) == 0)
		return (S);
	return (INVAL);
}

t_bool get_texture(const int fd, t_texture textures[])
{
	char *line = NULL;
	char **split = NULL;
	t_texture_enum text_index;

	if(get_next_line(fd, &line) && ft_strlen(line) > 3)
	{
		split = ft_split(line, ' ');
		text_index = texture_to_enum(split[0]);
		if(num_of_strings(split) != 2 || text_index == INVAL)
		{
			free(line);
			free_split(split);
			if(text_index == INVAL)
				return (INVALID);
			return (FALSE);
		}
		textures[text_index].filename = split[1];
		return (TRUE);
	}
	free(line);
	return (FALSE);
}

t_bool get_textures(const int fd, t_texture textures[])
{
	int i = 0;
	int ret;

	while(i < 5)
	{
		ret = get_texture(fd, textures);
		if(ret == INVALID)
			return (FALSE);
		if(ret)
			i++;
	}
	return (TRUE);
}

t_bool get_resolution(const int fd, t_window *window)
{
	char *line = NULL;
	char **split = NULL;

	if(get_next_line(fd, &line) > 0 && *line == 'R')
	{
		split = ft_split(line, ' ');
		if(num_of_strings(split) != 3)
		{
			free(line);
			free_split(split);
			return (FALSE);
		}
		window->width = ft_atoi(split[1]);
		window->height = ft_atoi(split[2]);
		free_split(split);
		free(line);
		if(window->width <= 0 || window->height <= 0)
			return (FALSE);
		return (TRUE);
	}
	free(line);
	return (FALSE);
}

t_bool parse_imput(const char *filename)
{
	(void)filename;
	return (TRUE);
}