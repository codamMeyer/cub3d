#include "ctest.h"
#include <game/sprite.h>
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

	for (i = 0; i < height; i++)
		for (j = 0; j < width; j++)
		{
			if (i == 0 || j == 0 || i == height - 1 || j == width - 1)
				map[i][j] = WALL;
			else
				map[i][j] = EMPTY;
		}
	return (map);
}

static void draw_map(t_data game)
{
	printf("\n");
	t_grid_position player_pos = to_grid_position(game.worldMap, game.player.position);
	for (int i = 0; i < game.worldMap.height; i++)
	{
		for (int j = 0; j < game.worldMap.width; j++)
		{
			if (player_pos.x == j && player_pos.y == i)
				printf("👦");
			else if (game.worldMap.matrix[i][j] == SPRITE)
				printf("🌲");
			else if (game.worldMap.matrix[i][j] == WALL)
				printf("🟫");
			else
				printf("  ");
		}
		printf("\n");
	}
	printf("\n");
}
CTEST_DATA(sprite_center_position)
{
	t_data game;
};

CTEST_SETUP(sprite_center_position)
{
	data->game.player.FOV = 60;
	data->game.player.speed = 10;

	data->game.worldMap.height = 5;
	data->game.worldMap.width = 7;
	data->game.worldMap.matrix = init_map(data->game.worldMap.height, data->game.worldMap.width);
}

CTEST_TEARDOWN(sprite_center_position)
{
	free_matrix(data->game.worldMap.matrix, data->game.worldMap.height);
}

CTEST2(sprite_center_position, player_facing_345_degrees_vertical)
{
	data->game.worldMap.matrix[2][3] = SPRITE;
	double expected_x = 4.0 * GRID_SIZE - (GRID_SIZE / 2.0);
	double expected_y = 3.0 * GRID_SIZE - (GRID_SIZE / 2.0);

	data->game.player.position.x = GRID_SIZE + 10;
	data->game.player.position.y = GRID_SIZE + 20;
	data->game.player.angle = 345;

	draw_map(data->game);

	double ray_angle = data->game.player.angle;
	ray_angle = fix_angle(ray_angle);
	t_sprite sprite = find_sprite_vertical_line(&(data->game), ray_angle);

	ASSERT_DBL_NEAR_TOL(expected_x, sprite.center.x, 1e-2);
	ASSERT_DBL_NEAR_TOL(expected_y, sprite.center.y, 1e-2);
}

CTEST2(sprite_center_position, player_facing_345_degrees_horizontal)
{
	data->game.worldMap.matrix[2][3] = 2;
	double expected_x = 4.0 * GRID_SIZE - (GRID_SIZE / 2.0);
	double expected_y = 3.0 * GRID_SIZE - (GRID_SIZE / 2.0);

	data->game.player.position.x = 76;
	data->game.player.position.y = 51;
	data->game.player.angle = 345;

	draw_map(data->game);

	double ray_angle = data->game.player.angle;
	ray_angle = fix_angle(ray_angle);
	t_sprite sprite = find_sprite_horizontal_line(&(data->game), ray_angle);

	ASSERT_DBL_NEAR_TOL(expected_x, sprite.center.x, 1e-2);
	ASSERT_DBL_NEAR_TOL(expected_y, sprite.center.y, 1e-2);
}

CTEST_DATA(find_sprite_list)
{
	t_data game;
	t_list *sprites;
};

CTEST_SETUP(find_sprite_list)
{
	data->game.player.FOV = 60;
	data->game.player.speed = 10;
	data->game.worldMap.height = 7;
	data->game.worldMap.width = 7;
	data->game.worldMap.matrix = init_map(data->game.worldMap.height, data->game.worldMap.width);
	data->sprites = NULL;
}

CTEST_TEARDOWN(find_sprite_list)
{
	ft_lstclear(&data->sprites, free);
	free_matrix(data->game.worldMap.matrix, data->game.worldMap.height);
}

CTEST2(find_sprite_list, player_facing_270_and_two_sprites)
{
	data->game.worldMap.matrix[3][2] = 2;
	data->game.worldMap.matrix[4][2] = 2;

	data->game.player.position.x = 76;
	data->game.player.position.y = 51;
	data->game.player.angle = 270;
	t_ray ray;
	ray.angle = 270;

	draw_map(data->game);
	find_sprites(&data->game, &data->sprites, ray.angle);
	ASSERT_EQUAL(2, ft_lstsize(data->sprites));

	// double ray_angle = data->game.player.angle;
	// ray_angle = fix_angle(ray_angle);
	// t_sprite sprite = find_sprite_horizontal_line(&(data->game), ray_angle);
}