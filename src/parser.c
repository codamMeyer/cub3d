#include <defs.h>
#include <fcntl.h>
#include <get_next_line.h>
#include <libft/libft.h>
#include <map.h>
#include <math_utils.h>
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

t_bool get_color(const char *line, t_color *color)
{
	unsigned char *address = (unsigned char *)color;
	char **split = NULL;
	int colors[3];
	t_bool ret = TRUE;
	split = ft_split(&line[1], ',');
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
	return (INVALID_TEXTURE);
}

t_bool get_texture(const char *line, t_texture textures[])
{
	char **split = NULL;
	t_texture_enum text_index;
	t_bool ret = FALSE;
	split = ft_split(line, ' ');
	text_index = texture_to_enum(split[0]);
	if(num_of_strings(split) == 2 && text_index != INVALID_TEXTURE)
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

t_bool check_file_extension(const char *filename)
{
	const int len = ft_strlen(filename);

	if(ft_strncmp(&filename[len - 4], ".cub", 4) == 0)
		return (TRUE);
	return (FALSE);
}

static t_bool is_map(const char *line)
{
	return (line[0] != '\0' && line[0] != 'R' && line[0] != 'F' && line[0] != 'C' &&
			!is_texture(line));
}

t_bool find_first_line_of_map(const int fd, char **line)
{
	while(get_next_line(fd, line))
	{
		if(is_map(*line))
			return (TRUE);
		free(*line);
	}
	return (FALSE);
}

t_bool get_map_dimentions(const int fd, char **line, t_map *map)
{
	int bytes_read;
	while(TRUE)
	{
		++(map->height);
		map->width = max_d(map->width, ft_strlen(*line));
		free(*line);
		bytes_read = get_next_line(fd, line);
		if(bytes_read < 0)
			break;
		if(bytes_read == 0)
		{
			if(ft_strlen(*line) > 0)
			{
				map->width = max_d(map->width, ft_strlen(*line));
				++(map->height);
			}
			free(*line);
			return (TRUE);
		}
	}
	return (FALSE);
}

t_bool init_map_matrix(const char *filename, t_map *map)
{
	const int fd = open(filename, O_RDONLY);
	char *line;
	int i;
	int j;
	int bytes_read;

	if(fd < 0)
		return (FALSE);
	if(!find_first_line_of_map(fd, &line))
	{
		free(line);
		return (FALSE);
	}
	map->matrix = malloc_matrix(map->height, map->width);
	i = 0;
	while(TRUE)
	{
		j = 0;
		while(j < map->width)
		{
			if(j >= ft_strlen(line))
				map->matrix[i][j] = 1;
			else if(line[j] == ' ' || line[j] == '1')
				map->matrix[i][j] = 1;
			else
				map->matrix[i][j] = 0;
			j++;
		}
		i++;
		free(line);
		bytes_read = get_next_line(fd, &line);
		if(bytes_read < 0)
			return (FALSE);
		if(i == map->height)
			break;
	}

	i = 0;
	while(i < map->height)
	{
		j = 0;
		while(j < map->width)
		{
			if((i == 0 || i == map->height - 1) && map->matrix[i][j] != 1)
				return (FALSE);
			if((j == 0 || j == map->width - 1) && map->matrix[i][j] != 1)
				return (FALSE);
			j++;
		}
		i++;
		free(line);
		bytes_read = get_next_line(fd, &line);
		if(bytes_read < 0)
			return (FALSE);
		if(i == map->height)
			break;
	}
	// free matrix if goes wrong
	return (TRUE);
}

t_bool parse_map(const char *filename, t_map *map)
{
	const int fd = open(filename, O_RDONLY);
	char *line = NULL;

	map->height = 0;
	map->width = 0;
	if(fd < 0)
		return (FALSE);
	if(!find_first_line_of_map(fd, &line))
	{
		free(line);
		return (FALSE);
	}
	return (get_map_dimentions(fd, &line, map));
}

t_bool parse_input(const char *filename,
				   t_window *window,
				   t_texture textures[],
				   t_color *floor,
				   t_color *ceiling,
				   t_map *map)
{
	const int fd = open(filename, O_RDONLY);
	char *line;
	t_bool ret = FALSE;
	(void)map;
	if(!check_file_extension(filename))
		return (ret);
	if(fd < 0)
		return (ret);
	while(get_next_line(fd, &line))
	{
		if(line[0] == 'R')
			ret = get_resolution(line, window);
		else if(is_texture(line))
			ret = get_texture(line, textures);
		else if(line[0] == 'F')
			ret = get_color(line, floor);
		else if(line[0] == 'C')
			ret = get_color(line, ceiling);
		if(ret == FALSE)
			break;
		free(line);
	}

	free(line);
	close(fd);
	return (ret);
}