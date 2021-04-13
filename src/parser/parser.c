#include "parser.h"
#include "map_parser.h"
#include "texture_parser.h"
#include "utils_parser.h"
#include <fcntl.h>
#include <libminift.h>
#include <utils/map_utils.h>

static t_bool	find_first_line_of_map(const int fd, char **line)
{
	while (get_next_line(fd, line) > 0)
	{
		if (is_map(*line))
			return (TRUE);
		free(*line);
	}
	return (FALSE);
}

static t_status	get_header_information(const char *filename, t_data *data)
{
	const int	fd = open(filename, O_RDONLY);
	char		*line;
	t_status	ret;

	ret = SUCCESS;
	if (fd < 0)
		return (FILE_ERROR);
	while (get_next_line(fd, &line) && ret == SUCCESS)
	{
		if (line[0] == 'R')
			ret = get_resolution(line, &data->screen);
		else if (is_texture(line))
			ret = get_texture(line, data->textures);
		else if (line[0] == 'F')
			ret = get_color(line, &data->floor);
		else if (line[0] == 'C')
			ret = get_color(line, &data->ceiling);
		free(line);
	}
	free(line);
	close(fd);
	return (ret);
}

t_status	get_resolution(const char *line, t_window *window)
{
	char		**split;
	t_status	ret;

	ret = RESOLUTION_ERROR;
	split = NULL;
	split = ft_split(line, ' ');
	if (!split)
		return (MALLOC_ERROR);
	if (num_of_strings(split) == 3)
	{
		window->width = ft_atoi(split[1]);
		window->height = ft_atoi(split[2]);
		if (window->width > 0 && window->height > 0)
			ret = SUCCESS;
	}
	free_split(split);
	return (ret);
}

t_status	check_file_extension(const char *filename)
{
	const int	len = ft_strlen(filename);

	if (ft_strncmp(&filename[len - 4], ".cub", 4) == 0)
		return (SUCCESS);
	return (EXTENSION_ERROR);
}

t_status	init_map_matrix(const char *filename, t_map *map, t_player *player)
{
	const int	fd = open(filename, O_RDONLY);
	char		*line;
	t_status	ret;

	if (fd < 0)
		return (FILE_ERROR);
	ret = SUCCESS;
	find_first_line_of_map(fd, &line);
	map->matrix = malloc_matrix(map->height, map->width);
	if (!map->matrix)
		ret = MALLOC_ERROR;
	else if (!populate_map(fd, map, &line))
		ret = (MALLOC_ERROR);
	else
		ret = check_map_content(map, player);
	if (ret != SUCCESS)
		free_matrix(map->matrix, map->height);
	close(fd);
	return (ret);
}

t_status	parse_map(const char *filename, t_map *map)
{
	const int	fd = open(filename, O_RDONLY);
	char		*line;
	t_status	ret;

	if (fd < 0)
		return (FILE_ERROR);
	ret = SUCCESS;
	map->height = 0;
	map->width = 0;
	if (!find_first_line_of_map(fd, &line))
	{
		free(line);
		close(fd);
		return (MISSING_MAP_ERROR);
	}
	ret = get_map_dimensions(fd, &line, map);
	close(fd);
	return (ret);
}

t_bool	init_sprites_array(t_data *data)
{
	data->sprites = malloc(sizeof(t_sprite) * data->worldMap.sprites_count);
	if (data->sprites == NULL)
	{
		free_matrix(data->worldMap.matrix, data->worldMap.height);
		return (MALLOC_ERROR);
	}
	return (SUCCESS);
}

t_status	parse_input(const char *filename, t_data *data)
{
	t_status	ret;

	ret = SUCCESS;
	ret = check_file_extension(filename);
	if (ret == SUCCESS)
		ret = get_header_information(filename, data);
	if (ret == SUCCESS)
		ret = parse_map(filename, &data->worldMap);
	if (ret == SUCCESS)
		ret = init_map_matrix(filename, &data->worldMap, &data->player);
	if (ret == SUCCESS)
		ret = init_sprites_array(data);
	return (ret);
}
