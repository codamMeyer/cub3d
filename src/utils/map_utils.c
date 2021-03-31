#include <stdio.h>
#include <stdlib.h>
#include <utils/map_utils.h>

int **malloc_matrix(int height, int width)
{
	int i;
	int **map = (int **)malloc(height * sizeof(int *));
	if(!map)
		return (NULL);
	for(i = 0; i < height; i++)
	{
		map[i] = (int *)malloc(width * sizeof(int));
		if(!map[i])
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
	while(i < height)
	{
		free(map[i]);
		++i;
	}
	free(map);
}

// int draw_map_2d(t_data *data)
// {
// 	int i;
// 	int j;
// 	int color;
// 	int x = 0;
// 	int y = 0;
// 	int grid_size = GRID_SIZE / 7;

// 	for(i = 0; i < data->worldMap.height; i++)
// 	{
// 		for(j = 0; j < data->worldMap.width; j++)
// 		{
// 			if(data->worldMap.matrix[i][j] > 0)
// 				color = WHITE;
// 			else
// 				color = BLACK;
// 			draw_square(&data->img, grid_size, x, y, color);
// 			x += grid_size;
// 		}
// 		x = 0;
// 		y += grid_size;
// 	}
// 	return (0);
// }
