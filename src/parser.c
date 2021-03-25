#include <defs.h>
#include <fcntl.h>
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

t_bool get_texture(const char *line, t_texture textures[])
{
	char **split = NULL;
	t_texture_enum text_index;
	t_bool ret = FALSE;
	split = ft_split(line, ' ');
	text_index = texture_to_enum(split[0]);
	if(num_of_strings(split) == 2 && text_index != INVAL)
	{
		ft_strcpy(&(textures[text_index].filename[0]), split[1]);
		ret = TRUE;
	}
	free_split(split);
	return (ret);
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

// t_bool get_textures(const int fd, t_texture textures[])
// {
// 	int i = 0;
// 	int ret;

// 	while(i < 5)
// 	{
// 		ret = get_texture(fd, textures);
// 		if(ret == INVALID)
// 			return (FALSE);
// 		if(ret)
// 			i++;
// 	}
// 	return (TRUE);
// }

t_bool get_resolution(const char *line, t_window *window)
{
	char **split = NULL;
	t_bool ret = FALSE;

	split = ft_split(line, ' ');
	if(num_of_strings(split) == 3)
	{
		window->width = ft_atoi(split[1]);
		window->height = ft_atoi(split[2]);
		if(window->width > 0 && window->height > 0)
			ret = TRUE;
	}
	free_split(split);
	return (ret);
}

t_bool parse_input(const char *filename)
{
	const int fd = open(filename, O_RDONLY);
	t_window window;
	t_texture textures[5] = {};
	char *line;

	if(fd < 0)
		return (FALSE);
	while(get_next_line(fd, &line))
	{
		if(line[0] == 'R')
		{
			get_resolution(line, &window); // check return
			free(line);
		}
		if(is_texture(line))
		{
			get_texture(line, textures); // check return
			free(line);
		}
	}
	free(line);
	return (TRUE);
}