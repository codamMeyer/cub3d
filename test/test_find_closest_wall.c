#include "ctest.h"

#include <inc/defs.h>
#include <inc/map.h>
#include <inc/player.h>
#include <inc/ray_casting_logic.h>
#include <inc/raycaster.h>
#include <inc/utils.h>
#include <inc/wall_detection.h>
#include <math.h>
#include <math_utils.h>
#include <stdio.h>
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
static void draw_map(t_data game, int expected_x, int expected_y)
{
	printf("\n");
	t_grid_position player_pos = to_grid_position(game.worldMap, game.player.position);
	for(int i = 0; i < game.worldMap.height; i++)
	{
		for(int j = 0; j < game.worldMap.width; j++)
		{
			if(player_pos.x == j && player_pos.y == i)
				printf("👦");
			else if((j == expected_x && i == expected_y) &&
					(expected_x != INVALID && expected_y != INVALID))
				printf("🔵");
			else if(game.worldMap.matrix[i][j] == 1)
				printf("🟫");
			else
				printf("  ");
		}
		printf("\n");
	}
	printf("\n");
}
CTEST_DATA(closer_wall)
{
	t_data game;
};

CTEST_SETUP(closer_wall)
{
	data->game.player.size = 5;
	data->game.player.FOV = 60;
	data->game.player.plane_x = 320;
	data->game.player.plane_y = 200;
	data->game.player.speed = 10;
	data->game.player.color = BLUE;
	data->game.worldMap.height = 5;
	data->game.worldMap.width = 7;
	data->game.worldMap.matrix = init_map(data->game.worldMap.height, data->game.worldMap.width);
	data->game.worldMap.matrix[2][3] = 1;
}

CTEST_TEARDOWN(closer_wall)
{
	free_matrix(data->game.worldMap.matrix, data->game.worldMap.height);
}

CTEST2(closer_wall, player_facing_345_degrees_horizontal)
{
	int expected_x = 4;
	int expected_y = 0;

	data->game.player.position.x = GRID_SIZE + 10;
	data->game.player.position.y = GRID_SIZE + 20;
	data->game.player.angle = 345;

	draw_map(data->game, expected_x, expected_y);

	double ray_angle = 10.00;
	ray_angle = fix_angle(ray_angle);
	t_position ray_position = find_wall_horizontal_line(&(data->game), ray_angle);

	t_grid_position ray_grid_position = to_grid_position(data->game.worldMap, ray_position);

	ASSERT_EQUAL(expected_x, ray_grid_position.x);
	ASSERT_EQUAL(expected_y, ray_grid_position.y);
}

CTEST2(closer_wall, player_facing_345_degrees_vertical)
{
	int expected_x = 5;
	int expected_y = 0;

	data->game.player.position.x = GRID_SIZE + 10;
	data->game.player.position.y = GRID_SIZE + 20;
	data->game.player.angle = 345;

	draw_map(data->game, expected_x, expected_y);

	double ray_angle = 10.00;
	ray_angle = fix_angle(ray_angle);
	t_position ray_position = find_wall_vertical_line(&(data->game), ray_angle);

	t_grid_position ray_grid_position = to_grid_position(data->game.worldMap, ray_position);

	ASSERT_EQUAL(expected_x, ray_grid_position.x);
	ASSERT_EQUAL(expected_y, ray_grid_position.y);
}