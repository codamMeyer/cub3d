#include "ctest.h"

#include <inc/game/player.h>
#include <inc/game/ray_casting_logic.h>
#include <inc/game/raycaster.h>
#include <inc/utils/utils.h>
#include <inc/utils/defs.h>
#include <inc/utils/map_utils.h>
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
				printf("🔸");
			else if(game.worldMap.matrix[i][j] == 1)
				printf("⬜️");
			else
				printf("  ");
		}
		printf("\n");
	}
	printf("\n");
}

CTEST_DATA(player_forward_move)
{
	t_data game;
};

CTEST_SETUP(player_forward_move)
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

CTEST_TEARDOWN(player_forward_move)
{
	free_matrix(data->game.worldMap.matrix, data->game.worldMap.height);
}

CTEST2(player_forward_move, player_facing_90_degrees)
{
	int expected_x = 1;
	int expected_y = 1;

	data->game.player.position.x = 48;
	data->game.player.position.y = 113;
	data->game.player.angle = 90;

	draw_map(data->game, expected_x, expected_y);

	while(1)
	{
		if(!move_forward(&data->game.player, &data->game))
			break;
	}

	draw_map(data->game, INVALID, INVALID);
	t_grid_position player_grid_position =
		to_grid_position(data->game.worldMap, data->game.player.position);

	ASSERT_EQUAL(expected_x, player_grid_position.x);
	ASSERT_EQUAL(expected_y, player_grid_position.y);
}

CTEST2(player_forward_move, player_facing_0_degrees)
{
	int expected_x = 5;
	int expected_y = 3;

	data->game.player.position.x = 48;
	data->game.player.position.y = 113;
	data->game.player.angle = 0;

	draw_map(data->game, expected_x, expected_y);
	while(1)
	{
		if(!move_forward(&data->game.player, &data->game))
			break;
	}

	draw_map(data->game, INVALID, INVALID);
	t_grid_position player_grid_position =
		to_grid_position(data->game.worldMap, data->game.player.position);

	ASSERT_EQUAL(expected_x, player_grid_position.x);
	ASSERT_EQUAL(expected_y, player_grid_position.y);
}

CTEST2(player_forward_move, player_facing_0_degrees_with_obstacle)
{
	int expected_x = 2;
	int expected_y = 2;

	data->game.player.position.x = 48;
	data->game.player.position.y = 80;
	data->game.player.angle = 0;

	draw_map(data->game, expected_x, expected_y);
	while(1)
	{
		if(!move_forward(&data->game.player, &data->game))
			break;
	}

	draw_map(data->game, INVALID, INVALID);
	t_grid_position player_grid_position =
		to_grid_position(data->game.worldMap, data->game.player.position);

	ASSERT_EQUAL(expected_x, player_grid_position.x);
	ASSERT_EQUAL(expected_y, player_grid_position.y);
}

CTEST2(player_forward_move, player_facing_270_degrees)
{
	int expected_x = 1;
	int expected_y = 3;

	data->game.player.position.x = 48;
	data->game.player.position.y = 48;
	data->game.player.angle = 270;

	draw_map(data->game, expected_x, expected_y);
	while(1)
	{
		if(!move_forward(&data->game.player, &data->game))
			break;
	}

	draw_map(data->game, INVALID, INVALID);
	t_grid_position player_grid_position =
		to_grid_position(data->game.worldMap, data->game.player.position);

	ASSERT_EQUAL(expected_x, player_grid_position.x);
	ASSERT_EQUAL(expected_y, player_grid_position.y);
}

CTEST2(player_forward_move, player_facing_230_degrees)
{
	int expected_x = 1;
	int expected_y = 3;

	data->game.player.position.x = 80;
	data->game.player.position.y = 80;
	data->game.player.angle = 230;

	draw_map(data->game, expected_x, expected_y);
	while(1)
	{
		if(!move_forward(&data->game.player, &data->game))
			break;
	}

	draw_map(data->game, INVALID, INVALID);
	t_grid_position player_grid_position =
		to_grid_position(data->game.worldMap, data->game.player.position);

	ASSERT_EQUAL(expected_x, player_grid_position.x);
	ASSERT_EQUAL(expected_y, player_grid_position.y);
}

CTEST2(player_forward_move, player_facing_220_degrees)
{
	int expected_x = 4;
	int expected_y = 2;

	data->game.player.position.x = 189;
	data->game.player.position.y = 37;
	data->game.player.angle = 220;

	draw_map(data->game, expected_x, expected_y);

	while(1)
	{
		if(!move_forward(&data->game.player, &data->game))
			break;
	}

	draw_map(data->game, INVALID, INVALID);
	t_grid_position player_grid_position =
		to_grid_position(data->game.worldMap, data->game.player.position);

	ASSERT_EQUAL(expected_x, player_grid_position.x);
	ASSERT_EQUAL(expected_y, player_grid_position.y);
}

CTEST2(player_forward_move, player_facing_180_degrees)
{
	int expected_x = 1;
	int expected_y = 1;

	data->game.player.position.x = 189;
	data->game.player.position.y = 37;
	data->game.player.angle = 180;

	draw_map(data->game, expected_x, expected_y);
	while(1)
	{
		if(!move_forward(&data->game.player, &data->game))
			break;
	}
	draw_map(data->game, INVALID, INVALID);
	t_grid_position player_grid_position =
		to_grid_position(data->game.worldMap, data->game.player.position);

	ASSERT_EQUAL(expected_x, player_grid_position.x);
	ASSERT_EQUAL(expected_y, player_grid_position.y);
}