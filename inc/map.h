#ifndef MAP_H
#define MAP_H
#ifndef GRID_SIZE
#	define GRID_SIZE 64
#endif
#include "defs.h"

int draw_map_2d(t_data *data);
int **init_matrix(int height, int width);
int **malloc_matrix(int height, int width);
void free_matrix(int **map, int height);

#endif