#include "libft.h"

static size_t	ft_min(size_t lhs, size_t rhs)
{
	if (lhs <= rhs)
		return (lhs);
	else
		return (rhs);
}

int	realloc_line(char **dest, t_file_state **file_state, int *ret)
{
	int	new_size;

	(*dest)[(*file_state)->line_index] = '\0';
	new_size = ((*file_state)->line_index + 1) * sizeof(char);
	*dest = ft_realloc(*dest, (*file_state)->line_size, new_size);
	if (*dest == NULL)
	{
		free(*file_state);
		*ret = ERROR;
		return (ERROR);
	}
	*ret = LINE_READ;
	return (0);
}

int	adjust_mem_size(t_file_state *f_state, char **dest)
{
	int	new_size;

	if (f_state->line_index == f_state->line_size)
	{
		new_size = (f_state->line_size + SIZE) * sizeof(char);
		*dest = ft_realloc(*dest, f_state->line_size, new_size);
		if (*dest == NULL)
			return (0);
		f_state->line_size += SIZE;
	}
	return (1);
}

void	*ft_realloc(void *ptr, size_t prev_size, size_t new_size)
{
	void			*new;
	const size_t	size = ft_min(prev_size, new_size);

	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}
	new = malloc(new_size);
	if (new == NULL)
	{
		free(ptr);
		return (NULL);
	}
	if (ptr != NULL)
	{
		ft_memcpy(new, ptr, size);
		free(ptr);
	}
	return (new);
}
