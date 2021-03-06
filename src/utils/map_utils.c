#include <stdio.h>
#include <stdlib.h>
#include <utils/map_utils.h>

int	**malloc_matrix(int height, int width)
{
	int	i;
	int	**map;

	map = (int **)malloc(height * sizeof(int *));
	if (!map)
		return (NULL);
	i = 0;
	while (i < height)
	{
		map[i] = (int *)malloc(width * sizeof(int));
		if (!map[i])
		{
			free_matrix(map, i);
			return (NULL);
		}
		++i;
	}
	return (map);
}

void	free_matrix(int **map, int height)
{
	int	i;

	i = 0;
	if (map == NULL)
		return ;
	while (i < height)
	{
		free(map[i]);
		++i;
	}
	free(map);
}
