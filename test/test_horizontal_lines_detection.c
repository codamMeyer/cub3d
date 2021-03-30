#include "ctest.h"

#include <inc/game/ray_casting_logic.h>
#include <inc/game/raycaster.h>
#include <inc/utils/utils.h>
#include <inc/utils/defs.h>
#include <inc/utils/map_utils.h>
#include <inc/game/wall_detection.h>
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

CTEST_DATA(horizontal_lines)
{
	t_data game;
};

CTEST_SETUP(horizontal_lines)
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
}

CTEST_TEARDOWN(horizontal_lines)
{
	free_matrix(data->game.worldMap.matrix, data->game.worldMap.height);
}

CTEST2(horizontal_lines, player_facing_90_degrees)
{
	int expected_x = 2;
	int expected_y = 0;

	data->game.player.position.x = 48;
	data->game.player.position.y = 80;
	data->game.player.angle = 90;

	draw_map(data->game, expected_x, expected_y);

	double ray_angle = data->game.player.angle - (data->game.player.FOV / 2);
	ray_angle = fix_angle(ray_angle);
	t_position ray_position = find_wall_horizontal_line(&(data->game), ray_angle);

	t_grid_position ray_grid_position = to_grid_position(data->game.worldMap, ray_position);

	ASSERT_EQUAL(expected_x, ray_grid_position.x);
	ASSERT_EQUAL(expected_y, ray_grid_position.y);
}

CTEST2(horizontal_lines, player_facing_60_degrees)
{
	int expected_x = 4;
	int expected_y = 0;
	data->game.player.position.x = 48;
	data->game.player.position.y = 80;
	data->game.player.angle = 60;
	draw_map(data->game, expected_x, expected_y);

	double ray_angle = data->game.player.angle - (data->game.player.FOV / 2);
	ray_angle = fix_angle(ray_angle);
	t_position ray_position = find_wall_horizontal_line(&(data->game), ray_angle);

	t_grid_position ray_grid_position = to_grid_position(data->game.worldMap, ray_position);

	ASSERT_EQUAL(expected_x, ray_grid_position.x);
	ASSERT_EQUAL(expected_y, ray_grid_position.y);
}

CTEST2(horizontal_lines, player_facing_0_degrees)
{
	int expected_x = 4;
	int expected_y = 4;
	data->game.player.position.x = 48;
	data->game.player.position.y = 80;
	data->game.player.angle = 0;
	draw_map(data->game, expected_x, expected_y);

	double ray_angle = data->game.player.angle - (data->game.player.FOV / 2);
	ray_angle = fix_angle(ray_angle);

	t_position ray_position = find_wall_horizontal_line(&(data->game), ray_angle);

	t_grid_position ray_grid_position = to_grid_position(data->game.worldMap, ray_position);

	ASSERT_EQUAL(expected_x, ray_grid_position.x);
	ASSERT_EQUAL(expected_y, ray_grid_position.y);
}

CTEST2(horizontal_lines, player_facing_30_degrees)
{
	int expected_x = INVALID;
	int expected_y = INVALID;
	data->game.player.position.x = 111;
	data->game.player.position.y = 79;
	data->game.player.angle = 30;

	draw_map(data->game, expected_x, expected_y);

	double ray_angle = data->game.player.angle - (data->game.player.FOV / 2);
	ray_angle = fix_angle(ray_angle);

	t_position ray_position = find_wall_horizontal_line(&(data->game), ray_angle);

	ASSERT_EQUAL(expected_x, ray_position.x);
	ASSERT_EQUAL(expected_y, ray_position.y);
}

CTEST2(horizontal_lines, player_facing_300_degrees)
{
	int expected_x = 1;
	int expected_y = 4;
	data->game.player.position.x = 48;
	data->game.player.position.y = 80;
	data->game.player.angle = 300;

	draw_map(data->game, expected_x, expected_y);

	double ray_angle = data->game.player.angle - (data->game.player.FOV / 2);
	ray_angle = fix_angle(ray_angle);

	t_position ray_position = find_wall_horizontal_line(&(data->game), ray_angle);

	t_grid_position ray_grid_position = to_grid_position(data->game.worldMap, ray_position);

	ASSERT_EQUAL(expected_x, ray_grid_position.x);
	ASSERT_EQUAL(expected_y, ray_grid_position.y);
}

CTEST2(horizontal_lines, player_facing_270_degrees)
{
	int expected_x = 2;
	int expected_y = 4;
	data->game.player.position.x = 111;
	data->game.player.position.y = 79;
	data->game.player.angle = 270;

	draw_map(data->game, expected_x, expected_y);

	double ray_angle = data->game.player.angle - (data->game.player.FOV / 2);
	ray_angle = fix_angle(ray_angle);

	t_position ray_position = find_wall_horizontal_line(&(data->game), ray_angle);

	t_grid_position ray_grid_position = to_grid_position(data->game.worldMap, ray_position);

	ASSERT_EQUAL(expected_x, ray_grid_position.x);
	ASSERT_EQUAL(expected_y, ray_grid_position.y);
}

CTEST2(horizontal_lines, player_facing_210_degrees)
{
	int expected_x = INVALID;
	int expected_y = INVALID;
	data->game.player.position.x = 111;
	data->game.player.position.y = 79;
	data->game.player.angle = 210;

	draw_map(data->game, expected_x, expected_y);

	double ray_angle = data->game.player.angle - (data->game.player.FOV / 2);
	ray_angle = fix_angle(ray_angle);

	t_position ray_position = find_wall_horizontal_line(&(data->game), ray_angle);

	ASSERT_EQUAL(expected_x, ray_position.x);
	ASSERT_EQUAL(expected_y, ray_position.y);
}

CTEST2(horizontal_lines, player_facing_180_degrees)
{
	int expected_x = 0;
	int expected_y = 0;
	data->game.player.position.x = 111;
	data->game.player.position.y = 79;
	data->game.player.angle = 180;

	draw_map(data->game, expected_x, expected_y);

	double ray_angle = data->game.player.angle - (data->game.player.FOV / 2);
	ray_angle = fix_angle(ray_angle);

	t_position ray_position = find_wall_horizontal_line(&(data->game), ray_angle);

	t_grid_position ray_grid_position = to_grid_position(data->game.worldMap, ray_position);

	ASSERT_EQUAL(expected_x, ray_grid_position.x);
	ASSERT_EQUAL(expected_y, ray_grid_position.y);
}

CTEST2(horizontal_lines, player_facing_140_degrees)
{
	int expected_x = 2;
	int expected_y = 0;
	data->game.player.position.x = 111;
	data->game.player.position.y = 79;
	data->game.player.angle = 140;

	draw_map(data->game, expected_x, expected_y);

	double ray_angle = data->game.player.angle - (data->game.player.FOV / 2);
	ray_angle = fix_angle(ray_angle);

	t_position ray_position = find_wall_horizontal_line(&(data->game), ray_angle);

	t_grid_position ray_grid_position = to_grid_position(data->game.worldMap, ray_position);

	ASSERT_EQUAL(expected_x, ray_grid_position.x);
	ASSERT_EQUAL(expected_y, ray_grid_position.y);
}

CTEST2(horizontal_lines, player_facing_120_degrees)
{
	int expected_x = 3;
	int expected_y = 0;
	data->game.player.position.x = 111;
	data->game.player.position.y = 79;
	data->game.player.angle = 120;

	draw_map(data->game, expected_x, expected_y);

	double ray_angle = data->game.player.angle - (data->game.player.FOV / 2);
	ray_angle = fix_angle(ray_angle);

	t_position ray_position = find_wall_horizontal_line(&(data->game), ray_angle);

	t_grid_position ray_grid_position = to_grid_position(data->game.worldMap, ray_position);

	ASSERT_EQUAL(expected_x, ray_grid_position.x);
	ASSERT_EQUAL(expected_y, ray_grid_position.y);
}