#include "parse_header.h"
#include <libft.h>
#include <fcntl.h>
#include "texture_parser.h"
#include "utils_parser.h"

static t_status	check_if_initialized(t_color floor, t_color ceiling)
{
	if (floor.initialized == TRUE && ceiling.initialized == TRUE)
		return (SUCCESS);
	return (COLOR_ERROR);
}

static t_bool	is_valid_width_and_height(char *width, char *height)
{
	while (*width != '\0')
	{
		if (!ft_isdigit(*width))
			return (FALSE);
		++width;
	}
	while (*height != '\0')
	{
		if (!ft_isdigit(*height))
			return (FALSE);
		++height;
	}
	return (TRUE);
}

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
		if (ft_strncmp(line, "R ", 2) == 0)
			ret = get_resolution(line, &data->screen);
		else if (is_texture(line))
			ret = get_texture(line, data->textures);
		else if (ft_strncmp(line, "F ", 2) == 0)
			ret = get_color(line, &data->floor);
		else if (ft_strncmp(line, "C ", 2) == 0)
			ret = get_color(line, &data->ceiling);
		free(line);
	}
	if (ret == SUCCESS)
		ret = check_if_initialized(data->floor, data->ceiling);
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
	if (num_of_strings(split) == 3 && \
		is_valid_width_and_height(split[1], split[2]))
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
