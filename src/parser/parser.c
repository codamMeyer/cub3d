#include <fcntl.h>
#include <gnl/get_next_line.h>
#include <libft.h>
#include <parser/map_parser.h>
#include <parser/parser.h>
#include <parser/texture_parser.h>
#include <parser/utils_parser.h>
#include <utils/map_utils.h>

t_status get_resolution(const char *line, t_window *window)
{
	char **split = NULL;
	t_status ret = RESOLUTION_ERROR;

	split = ft_split(line, ' ');
	if(!split)
		return (MALLOC_ERROR);
	if(num_of_strings(split) == 3)
	{
		window->width = ft_atoi(split[1]);
		window->height = ft_atoi(split[2]);
		if(window->width > 0 && window->height > 0)
			ret = SUCCESS;
	}
	free_split(split);
	return (ret);
}

t_status check_file_extension(const char *filename)
{
	const int len = ft_strlen(filename);

	if(ft_strncmp(&filename[len - 4], ".cub", 4) == 0)
		return (SUCCESS);
	return (EXTENSION_ERROR);
}

static t_bool find_first_line_of_map(const int fd, char **line)
{
	while(get_next_line(fd, line) > 0)
	{
		if(is_map(*line))
			return (TRUE);
		free(*line);
	}
	return (FALSE);
}

t_status init_map_matrix(const char *filename, t_map *map, t_player *player)
{
	const int fd = open(filename, O_RDONLY);
	char *line;
	t_status ret;

	if(fd < 0)
		return (FILE_ERROR);
	ret = SUCCESS;
	find_first_line_of_map(fd, &line);
	map->matrix = malloc_matrix(map->height, map->width);
	if(!map->matrix)
		ret = MALLOC_ERROR;
	if(ret == SUCCESS)
		ret = populate_map(fd, map, &line);
	if(ret == SUCCESS)
		ret = check_map_content(map, player);
	close(fd);
	return (ret);
}

t_status parse_map(const char *filename, t_map *map)
{
	const int fd = open(filename, O_RDONLY);
	char *line;
	t_status ret;

	if(fd < 0)
		return (FILE_ERROR);
	ret = SUCCESS;
	map->height = 0;
	map->width = 0;
	if(!find_first_line_of_map(fd, &line))
	{
		free(line);
		close(fd);
		return (MISSING_MAP_ERROR);
	}
	ret = get_map_dimentions(fd, &line, map);
	close(fd);
	return (ret);
}

static t_status get_header_information(const char *filename,
									   t_window *window,
									   t_texture textures[],
									   t_color *floor,
									   t_color *ceiling)
{
	const int fd = open(filename, O_RDONLY);
	char *line;
	t_status ret = SUCCESS;
	if(fd < 0)
		return (FILE_ERROR);
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
		if(ret != SUCCESS)
			break;
		free(line);
	}
	free(line);
	close(fd);
	return (ret);
}

t_status parse_input(const char *filename, t_data *data)
{
	t_status ret;

	ret = SUCCESS;
	ret = check_file_extension(filename);
	if(ret == SUCCESS)
		ret = get_header_information(
			filename, &data->screen, data->textures, &data->floor, &data->ceiling);
	if(ret == SUCCESS)
		ret = parse_map(filename, &data->worldMap);
	if(ret == SUCCESS)
		ret = init_map_matrix(filename, &data->worldMap, &data->player);
	return (ret);
}