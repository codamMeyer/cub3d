#include "ctest.h"

#include <game/wall_detection.h>
#include <inc/game/game.h>
#include <inc/game/player.h>
#include <inc/game/ray_casting_logic.h>
#include <inc/utils/defs.h>
#include <inc/utils/map_utils.h>
#include <inc/utils/utils.h>
#include <math.h>
#include <stdio.h>
#include <utils/math_utils.h>

static int **init_map(int height, int width)
{
	int i, j;
	int **map = malloc_matrix(height, width);

	for(i = 0; i < height; i++)
		for(j = 0; j < width; j++)
		{
			if(i == 0 || j == 0 || i == height - 1 || j == width - 1)
				map[i][j] = 1;
			else
				map[i][j] = 0;
		}
	return (map);
}

CTEST_DATA(wall_distance)
{
	t_data game;
};

CTEST_SETUP(wall_distance)
{

	data->game.player.FOV = 60;

	data->game.player.speed = 10;

	data->game.worldMap.height = 5;
	data->game.worldMap.width = 7;
	data->game.worldMap.matrix = init_map(data->game.worldMap.height, data->game.worldMap.width);
	data->game.worldMap.matrix[2][3] = 1;
}

CTEST_TEARDOWN(wall_distance)
{
	free_matrix(data->game.worldMap.matrix, data->game.worldMap.height);
}

CTEST2(wall_distance, player_facing_90_degrees)
{
	double expected_dist = 55.94;

	data->game.player.position.x = 48;
	data->game.player.position.y = 80;

	t_position ray_position = {.x = 75, .y = 31};

	double wall_dist = get_distance_from_player(ray_position, data->game.player.position);

	ASSERT_DBL_NEAR_TOL(expected_dist, wall_dist, 1e-2);
}

CTEST2(wall_distance, player_facing_270_degrees)
{
	double expected_dist = 30.52;
	data->game.player.position.x = 48;
	data->game.player.position.y = 80;

	t_position ray_position = {.x = 32, .y = 106};

	double wall_dist = get_distance_from_player(ray_position, data->game.player.position);

	ASSERT_DBL_NEAR_TOL(expected_dist, wall_dist, 1e-2);
}
