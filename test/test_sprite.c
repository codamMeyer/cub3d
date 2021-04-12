#include "ctest.h"
#include <game/game.h>
#include <libft.h>
#include <sprite/sprite.h>
#include <stdio.h>
#include <utils/angle_utils.h>
#include <utils/map_utils.h>

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

CTEST_DATA(find_sprite_list)
{
	t_data game;
	t_sprite *sprites;
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
	free(data->sprites);
	free_matrix(data->game.worldMap.matrix, data->game.worldMap.height);
}

CTEST2(find_sprite_list, no_sprites)
{
	data->game.player.position.x = 76;
	data->game.player.position.y = 51;
	data->game.player.angle = 270;
	t_ray ray;
	ray.angle = 270;

	draw_map(data->game);
	find_sprites(data->game.player, data->game.worldMap, data->sprites, ray.angle);
}

CTEST2_SKIP(find_sprite_list, one_sprite)
{
	data->game.worldMap.matrix[4][3] = 2;

	data->game.player.position.x = 51;
	data->game.player.position.y = 76;
	data->game.player.angle = 270;
	t_ray ray;
	ray.angle = 305;

	draw_map(data->game);
	find_sprites(data->game.player, data->game.worldMap, data->sprites, ray.angle);
	sort_sprites(data->sprites, 1);
}

CTEST2_SKIP(find_sprite_list, test_sort)
{
	const int num_sprites = 3;
	t_sprite sprites[3];
	sprites[0].dist_from_player = 1.0;
	sprites[1].dist_from_player = 5.0;
	sprites[2].dist_from_player = 9.0;

	(void)data;
	// sort_sprites(&sprites);

	const double expected_dist[3] = {9.0, 5.0, 1.0};
	for (int i = 0; i < num_sprites; ++i)
	{
		ASSERT_EQUAL(expected_dist[i], sprites[i].dist_from_player);
	}
}
