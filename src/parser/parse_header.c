#include "parse_header.h"
#include <libft.h>
#include <fcntl.h>
#include "texture_parser.h"
#include "utils_parser.h"

t_status	get_header_information(const char *filename, t_data *data)
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
