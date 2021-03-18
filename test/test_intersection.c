#include "ctest.h"
#include <inc/defs.h>
#include <inc/map.h>
#include <inc/raycaster.h>
#include <inc/utils.h>
#include <math.h>
#include <math_utils.h>
#include <stdio.h>
#include <inc/ray_casting_logic.h>

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

CTEST_DATA(intersection)
{
	t_data game;
};

CTEST_SETUP(intersection)
{
	data->game.player.size = 5;
	data->game.player.FOV = 60;
	data->game.player.plane_x = 320;
	data->game.player.plane_y = 200;
	data->game.player.speed = 10;
	data->game.player.color = BLUE;
	data->game.worldMap.height = 10;
	data->game.worldMap.width = 10;
	data->game.worldMap.matrix = init_matrix(data->game.worldMap.height, data->game.worldMap.width);
	data->game.worldMap.matrix[3][3] = 1;
}

CTEST_TEARDOWN(intersection)
{
	free_matrix(data->game.worldMap.matrix, data->game.worldMap.height);
}

CTEST2(intersection, ray_angle_321_horizontal_detection)
{
	int expected_x = 3;
	int expected_y = 3;

	data->game.player.position.x = 42;
	data->game.player.position.y = 52;
	data->game.player.angle = 345;

	draw_map(data->game, expected_x, expected_y);

	double ray_angle = 321;
	t_position ray_position = find_horizontal_line(&(data->game), ray_angle);

	t_grid_position ray_grid_position = to_grid_position(data->game.worldMap, ray_position);

	ASSERT_EQUAL(expected_x, ray_grid_position.x);
	ASSERT_EQUAL(expected_y, ray_grid_position.y);
}

CTEST2(intersection, ray_angle_321_vertical_detection)
{
	int expected_x = 9;
	int expected_y = 7;

	data->game.player.position.x = 42;
	data->game.player.position.y = 52;
	data->game.player.angle = 345;

	draw_map(data->game, expected_x, expected_y);

	double ray_angle = 321;
	t_position ray_position = find_vertical_line(&(data->game), ray_angle);

	t_grid_position ray_grid_position = to_grid_position(data->game.worldMap, ray_position);

	ASSERT_EQUAL(expected_x, ray_grid_position.x);
	ASSERT_EQUAL(expected_y, ray_grid_position.y);
}