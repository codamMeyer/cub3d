#include "ctest.h"
#include <inc/defs.h>
#include <inc/map.h>
#include <inc/raycaster.h>
#include <inc/utils.h>
#include <math.h>
#include <stdio.h>
#include <math_utils.h>

static void draw_map(t_data game, int expected_x, int expected_y)
{
	printf("\n");
	t_grid_position player_pos = to_grid_position(game.worldMap, game.player.position);
	for (int i = 0; i < game.worldMap.height; i++)
	{
		for (int j = 0; j < game.worldMap.width; j++)
		{
			if (player_pos.x == j && player_pos.y == i)
				printf("👦");
			else if ((j == expected_x && i == expected_y) &&
					 (expected_x != INVALID && expected_y != INVALID))
				printf("🟢");
			else if (game.worldMap.matrix[i][j] == 1)
				printf("🟫");
			else
				printf("  ");
		}
		printf("\n");
	}
	printf("\n");
}

CTEST_DATA(vertical_lines)
{
	t_data game;
};

CTEST_SETUP(vertical_lines)
{
	data->game.player.size = 5;
	data->game.player.FOV = 60;
	data->game.player.plane_x = 320;
	data->game.player.plane_y = 200;
	data->game.player.speed = 10;
	data->game.player.color = BLUE;
	data->game.worldMap.height = 5;
	data->game.worldMap.width = 7;
	data->game.worldMap.matrix = init_matrix(data->game.worldMap.height, data->game.worldMap.width);
}

CTEST_TEARDOWN(vertical_lines)
{
	free_matrix(data->game.worldMap.matrix, data->game.worldMap.height);
}

CTEST2(vertical_lines, player_facing_90_degrees)
{
	int expected_x = 3;
	int expected_y = 0;

	data->game.player.position.x = 48;
	data->game.player.position.y = 88;
	data->game.player.angle = 90;

	draw_map(data->game, expected_x, expected_y);

	double ray_angle = data->game.player.angle - (data->game.player.FOV / 2);
	t_position ray_position = find_vertical_line(&(data->game), ray_angle);

	t_grid_position ray_grid_position = to_grid_position(data->game.worldMap, ray_position);

	ASSERT_EQUAL(expected_x, ray_grid_position.x);
	ASSERT_EQUAL(expected_y, ray_grid_position.y);
}

CTEST2(vertical_lines, player_facing_60_degrees)
{
	int expected_x = 5;
	int expected_y = 0;

	data->game.player.position.x = 48;
	data->game.player.position.y = 80;
	data->game.player.angle = 60;

	draw_map(data->game, expected_x, expected_y);

	double ray_angle = data->game.player.angle - (data->game.player.FOV / 2);
	t_position ray_position = find_vertical_line(&(data->game), ray_angle);

	t_grid_position ray_grid_position = to_grid_position(data->game.worldMap, ray_position);

	ASSERT_EQUAL(expected_x, ray_grid_position.x);
	ASSERT_EQUAL(expected_y, ray_grid_position.y);
}

CTEST2(vertical_lines, player_facing_30_degrees)
{
	int expected_x = 6;
	int expected_y = 2;

	data->game.player.position.x = 48;
	data->game.player.position.y = 80;
	data->game.player.angle = 30;

	draw_map(data->game, expected_x, expected_y);

	double ray_angle = data->game.player.angle - (data->game.player.FOV / 2);
	t_position ray_position = find_vertical_line(&(data->game), ray_angle);

	t_grid_position ray_grid_position = to_grid_position(data->game.worldMap, ray_position);

	ASSERT_EQUAL(expected_x, ray_grid_position.x);
	ASSERT_EQUAL(expected_y, ray_grid_position.y);
}

CTEST2(vertical_lines, player_facing_0_degrees)
{
	int expected_x = 5;
	int expected_y = 4;

	data->game.player.position.x = 48;
	data->game.player.position.y = 80;
	data->game.player.angle = 0;

	draw_map(data->game, expected_x, expected_y);

	double ray_angle = data->game.player.angle - (data->game.player.FOV / 2);
	t_position ray_position = find_vertical_line(&(data->game), ray_angle);

	t_grid_position ray_grid_position = to_grid_position(data->game.worldMap, ray_position);

	ASSERT_EQUAL(expected_x, ray_grid_position.x);
	ASSERT_EQUAL(expected_y, ray_grid_position.y);
}

CTEST2(vertical_lines, player_facing_300_degrees)
{
	int expected_x = INVALID;
	int expected_y = INVALID;

	data->game.player.position.x = 48;
	data->game.player.position.y = 80;
	data->game.player.angle = 300;

	draw_map(data->game, expected_x, expected_y);

	double ray_angle = data->game.player.angle - (data->game.player.FOV / 2);
	t_position ray_position = find_vertical_line(&(data->game), ray_angle);

	ASSERT_EQUAL(expected_x, ray_position.x);
	ASSERT_EQUAL(expected_y, ray_position.y);
}

CTEST2(vertical_lines, player_facing_270_degrees)
{
	int expected_x = INVALID;
	int expected_y = INVALID;

	data->game.player.position.x = 120;
	data->game.player.position.y = 80;
	data->game.player.angle = 270;

	draw_map(data->game, expected_x, expected_y);

	double ray_angle = data->game.player.angle - (data->game.player.FOV / 2);
	t_position ray_position = find_vertical_line(&(data->game), ray_angle);

	t_grid_position ray_grid_position = to_grid_position(data->game.worldMap, ray_position);

	ASSERT_EQUAL(expected_x, ray_grid_position.x);
	ASSERT_EQUAL(expected_y, ray_grid_position.y);
}

CTEST2(vertical_lines, player_facing_210_degrees)
{
	int expected_x = 0;
	int expected_y = 2;

	data->game.player.position.x = 120;
	data->game.player.position.y = 80;
	data->game.player.angle = 210;

	draw_map(data->game, expected_x, expected_y);

	double ray_angle = data->game.player.angle - (data->game.player.FOV / 2);
	t_position ray_position = find_vertical_line(&(data->game), ray_angle);

	t_grid_position ray_grid_position = to_grid_position(data->game.worldMap, ray_position);

	ASSERT_EQUAL(expected_x, ray_grid_position.x);
	ASSERT_EQUAL(expected_y, ray_grid_position.y);
}

CTEST2(vertical_lines, player_facing_180_degrees)
{
	int expected_x = 0;
	int expected_y = 0;

	data->game.player.position.x = 120;
	data->game.player.position.y = 80;
	data->game.player.angle = 180;

	draw_map(data->game, expected_x, expected_y);

	double ray_angle = data->game.player.angle - (data->game.player.FOV / 2);
	t_position ray_position = find_vertical_line(&(data->game), ray_angle);

	t_grid_position ray_grid_position = to_grid_position(data->game.worldMap, ray_position);

	ASSERT_EQUAL(expected_x, ray_grid_position.x);
	ASSERT_EQUAL(expected_y, ray_grid_position.y);
}

CTEST2(vertical_lines, player_facing_140_degrees)
{
	int expected_x = 2;
	int expected_y = 0;

	data->game.player.position.x = 120;
	data->game.player.position.y = 80;
	data->game.player.angle = 140;

	draw_map(data->game, expected_x, expected_y);

	double ray_angle = data->game.player.angle - (data->game.player.FOV / 2);
	t_position ray_position = find_vertical_line(&(data->game), ray_angle);

	t_grid_position ray_grid_position = to_grid_position(data->game.worldMap, ray_position);

	ASSERT_EQUAL(expected_x, ray_grid_position.x);
	ASSERT_EQUAL(expected_y, ray_grid_position.y);
}

CTEST2(vertical_lines, player_facing_120_degrees)
{
	int expected_x = INVALID;
	int expected_y = INVALID;

	data->game.player.position.x = 120;
	data->game.player.position.y = 80;
	data->game.player.angle = 120;

	draw_map(data->game, expected_x, expected_y);

	double ray_angle = data->game.player.angle - (data->game.player.FOV / 2);
	t_position ray_position = find_vertical_line(&(data->game), ray_angle);

	ASSERT_EQUAL(expected_x, ray_position.x);
	ASSERT_EQUAL(expected_y, ray_position.y);
}
