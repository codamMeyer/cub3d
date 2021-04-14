#include "libft.h"

static int	populate_line(char **dest, t_file_state *file_state, int *ret)
{
	char	cur;

	while (file_state->bytes_left)
	{
		cur = file_state->buffer[file_state->buffer_index];
		--file_state->bytes_left;
		++file_state->buffer_index;
		if (cur == '\n')
		{
			if (realloc_line(dest, &file_state, ret) == ERROR)
				return (ERROR);
			file_state->line_index = 0;
			return (LINE_READ);
		}
		(*dest)[file_state->line_index] = cur;
		++(file_state->line_index);
		if (!adjust_mem_size(file_state, dest))
			return (ERROR);
	}
	return (0);
}

static t_file_state	*initialize_file_state(t_file_state **file_state,
											char **line)
{
	if (*file_state == NULL)
	{
		*file_state = malloc(sizeof(t_file_state));
		if (*file_state == NULL)
			return (NULL);
		(*file_state)->buffer_index = 0;
		(*file_state)->bytes_left = 0;
		(*file_state)->line_index = 0;
		(*file_state)->line_size = 0;
	}
	*line = malloc(SIZE * sizeof(char));
	if (*line == NULL)
	{
		free(*file_state);
		return (NULL);
	}
	(*file_state)->line_size = SIZE;
	return (*file_state);
}

static int	is_valid_input(int fd)
{
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	return (1);
}

static t_bool	eof_or_error(int *bytes_read,
							char **line,
							t_file_state **file_state,
							int *ret)
{
	if (*bytes_read <= 0)
	{
		if (*bytes_read == 0)
			realloc_line(line, file_state, ret);
		*ret = *bytes_read;
		free(*file_state);
		*file_state = NULL;
		return (1);
	}
	return (0);
}

int	get_next_line(int fd, char **line)
{
	static t_file_state	*files[MAX_FD];
	int					bytes_read;
	t_file_state		*file_state;
	int					ret;

	if (!is_valid_input(fd))
		return (ERROR);
	file_state = initialize_file_state(&files[fd], line);
	if (file_state == NULL)
		return (ERROR);
	while (1)
	{
		if (file_state->bytes_left == 0)
		{
			bytes_read = read(fd, &file_state->buffer[0], BUFFER_SIZE);
			if (eof_or_error(&bytes_read, line, &files[fd], &ret))
				return (ret);
			file_state->bytes_left = bytes_read;
			file_state->buffer_index = 0;
		}
		if (populate_line(line, file_state, &ret))
			return (ret);
	}
	return (0);
}
