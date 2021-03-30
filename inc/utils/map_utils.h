#ifndef MAP_UTILS_H
#define MAP_UTILS_H
#ifndef GRID_SIZE
#	define GRID_SIZE 64
#endif
#include <utils/defs.h>

int draw_map_2d(t_data *data);
int **init_matrix(int height, int width);
int **malloc_matrix(int height, int width);
void free_matrix(int **map, int height);

#endif