#ifndef MAP_H
#define MAP_H
#define mapWidth 24
#define mapHeight 24
#define GRID_SIZE 32
#define MAP_WIDTH_PIX (mapWidth * GRID_SIZE)
#define MAP_HEIGHT_PIX (mapHeight * GRID_SIZE)
#include "defs.h"

int draw_map_2d(t_data *data);
int **init_world(int height, int width);
void free_matrix(int **map, int height);

#endif