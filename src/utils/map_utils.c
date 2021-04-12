#include <stdio.h>
#include <stdlib.h>
#include <utils/map_utils.h>

int **malloc_matrix(int height, int width)
{
	int i;
	int **map = (int **)malloc(height * sizeof(int *));
	if (!map)
		return (NULL);
	for (i = 0; i < height; i++)
	{
		map[i] = (int *)malloc(width * sizeof(int));
		if (!map[i])
		{
			free_matrix(map, i);
			return (NULL);
		}
	}
	return (map);
}

void free_matrix(int **map, int height)
{
	int i;
	i = 0;
	if (!map)
		return;
	while (i < height)
	{
		free(map[i]);
		++i;
	}
	free(map);
}