#include "ctest.h"
#include <inc/defs.h>
#include <inc/map.h>
#include <inc/player.h>
#include <inc/raycaster.h>
#include <inc/utils.h>
#include <math.h>
#include <math_utils.h>
#include <stdio.h>

CTEST_DATA(wall_distance)
{
	t_data game;
};

CTEST_SETUP(wall_distance)
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

	double wall_dist = get_wall_distance(ray_position, data->game.player.position);

	ASSERT_DBL_NEAR_TOL(expected_dist, wall_dist, 1e-2);
}

CTEST2(wall_distance, player_facing_270_degrees)
{
	double expected_dist = 30.52;
	data->game.player.position.x = 48;
	data->game.player.position.y = 80;

	t_position ray_position = {.x = 32, .y = 106};

	double wall_dist = get_wall_distance(ray_position, data->game.player.position);

	ASSERT_DBL_NEAR_TOL(expected_dist, wall_dist, 1e-2);
}

// CTEST2(wall_distance, player_facing_110_degrees)
// {
//     int expected_x = 1;
//     int expected_y = 4;
//     double expected_dist = 51.544;

//     data->game.player.position.x = 48;
//     data->game.player.position.y = 80;
//     data->game.player.angle = 110;

//     draw_map(data->game, expected_x, expected_y);

//     double ray_angle = data->game.player.angle - (data->game.player.FOV / 2);
//     t_position ray_position = find_horizontal_line(&(data->game), ray_angle);
//     double wall_dist = get_wall_distance(ray_position, data->game.player.position);

//     printf("%f\n", wall_dist);
//     ASSERT_DBL_NEAR(expected_dist, wall_dist);
// }