#ifndef MAP_H
#define MAP_H
#define mapWidth 5
#define mapHeight 5
#define GRID_SIZE 64
#define MAP_WIDTH_PIX (mapWidth * GRID_SIZE)
#define MAP_HEIGHT_PIX (mapHeight * GRID_SIZE)
#include "defs.h"

int draw_map_2d(t_data *data);
int **init_matrix(int height, int width);
void free_matrix(int **map, int height);

#endif