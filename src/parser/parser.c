#include "map_parser.h"
#include "parser.h"
#include "parse_header.h"
#include "utils_parser.h"
#include <fcntl.h>
#include <libft.h>
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

static t_bool	init_sprites_array(t_data *data)
{
	data->sprites = malloc(sizeof(t_sprite) * data->worldMap.sprites_count);
	if (data->sprites == NULL)
		return (MALLOC_ERROR);
	return (SUCCESS);
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

t_status	parse_input(const char *filename, t_data *data)
{
	t_status	ret;

	data->worldMap.matrix = NULL;
	data->sprites = NULL;
	data->img.addr = NULL;
	data->img.mlx = NULL;
	data->img.window = NULL;
	data->floor.initialized = FALSE;
	data->ceiling.initialized = FALSE;
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
