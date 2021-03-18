#include <map.h>
#include <stdlib.h>
#include <utils.h>

static int **malloc_matrix(int height, int width)
{
	int i;
	int **map = (int **)malloc(height * sizeof(int *));
	for(i = 0; i < height; i++)
		map[i] = (int *)malloc(width * sizeof(int));
	return (map);
}

int draw_map_2d(t_data *data)
{
	int i;
	int j;
	int color;
	int x = 0;
	int y = 0;
	int grid_size = GRID_SIZE / 7;

	for(i = 0; i < data->worldMap.height; i++)
	{
		for(j = 0; j < data->worldMap.width; j++)
		{
			if(data->worldMap.matrix[i][j] > 0)
				color = WHITE;
			else
				color = BLACK;
			draw_square(&data->map, grid_size, x, y, color);
			x += grid_size;
		}
		x = 0;
		y += grid_size;
	}
	return (0);
}

int **init_matrix(int height, int width)
{
	int i, j;
	int my_map[25][25] = {
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 0, 0, 2, 0, 0, 1, 0, 0, 2, 0, 0, 0, 1, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 2, 0, 0, 1, 0, 0, 2, 0, 0, 0, 1, 0, 0, 0, 2, 0, 0, 0, 1, 0, 0, 1},
		{1, 0, 0, 2, 0, 0, 1, 0, 0, 2, 0, 0, 0, 1, 0, 0, 0, 2, 0, 0, 0, 1, 0, 0, 1},
		{1, 0, 0, 2, 0, 0, 1, 0, 0, 2, 0, 0, 0, 1, 0, 0, 0, 2, 0, 0, 0, 1, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 1, 0, 0, 2, 0, 0, 0, 1, 0, 0, 0, 2, 0, 0, 0, 1, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 1, 0, 0, 2, 0, 0, 0, 1, 0, 0, 0, 2, 0, 0, 0, 1, 0, 0, 1},
		{1, 0, 0, 0, 2, 0, 1, 0, 0, 2, 0, 0, 0, 1, 0, 0, 0, 2, 0, 0, 0, 1, 0, 0, 1},
		{1, 0, 0, 0, 2, 0, 1, 0, 0, 2, 0, 0, 0, 1, 0, 0, 0, 2, 0, 0, 0, 1, 0, 0, 1},
		{1, 0, 0, 0, 2, 0, 1, 0, 0, 2, 0, 0, 0, 1, 0, 0, 0, 2, 0, 0, 0, 1, 0, 0, 1},
		{1, 0, 0, 0, 2, 0, 1, 0, 0, 2, 0, 0, 0, 1, 0, 0, 0, 2, 0, 0, 0, 1, 0, 0, 1},
		{1, 0, 0, 0, 2, 0, 1, 0, 0, 2, 0, 0, 0, 1, 0, 0, 0, 2, 0, 0, 0, 1, 0, 0, 1},
		{1, 0, 0, 0, 2, 0, 1, 0, 0, 2, 0, 0, 0, 1, 0, 0, 0, 2, 0, 0, 0, 1, 0, 0, 1},
		{1, 0, 0, 0, 2, 0, 1, 0, 0, 2, 0, 0, 0, 1, 0, 0, 0, 2, 0, 0, 0, 1, 0, 0, 1},
		{1, 0, 0, 0, 2, 0, 1, 0, 0, 2, 0, 0, 0, 1, 0, 0, 0, 2, 0, 0, 0, 1, 0, 0, 1},
		{1, 0, 0, 0, 2, 0, 1, 0, 0, 2, 0, 0, 0, 1, 0, 0, 0, 2, 0, 0, 0, 1, 0, 0, 1},
		{1, 0, 0, 0, 2, 0, 1, 0, 0, 2, 0, 0, 0, 1, 0, 0, 0, 2, 0, 0, 0, 1, 0, 0, 1},
		{1, 0, 0, 0, 2, 0, 1, 0, 0, 2, 2, 0, 0, 1, 0, 0, 0, 2, 0, 0, 0, 1, 0, 0, 1},
		{1, 0, 0, 0, 2, 0, 1, 0, 0, 0, 2, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
		{1, 0, 0, 0, 0, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	};

	int **map = malloc_matrix(height, width);

	for(i = 0; i < height; i++)
		for(j = 0; j < width; j++)
		{
			// if(i == 0 || j == 0 || i == height - 1 || j == width - 1)
			// 	map[i][j] = wall;
			// else
			// 	map[i][j] = empty;
			map[i][j] = my_map[i][j];
		}
	return (map);
}

void free_matrix(int **map, int height)
{
	int i;
	for(i = 0; i < height; i++)
		free(map[i]);
	free(map);
}