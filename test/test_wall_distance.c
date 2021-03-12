#include "ctest.h"
#include <inc/defs.h>
#include <inc/map.h>
#include <inc/player.h>
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
                printf("⚪️");
            else if (game.worldMap.matrix[i][j] == 1)
                printf("⬛️");
            else
                printf("  ");
        }
        printf("\n");
    }
    printf("\n");
}

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
    int expected_x = 2;
    int expected_y = 0;
    double expected_dist = 55.68;

    data->game.player.position.x = 48;
    data->game.player.position.y = 80;
    data->game.player.angle = 90;

    draw_map(data->game, expected_x, expected_y);

    double ray_angle = data->game.player.angle - (data->game.player.FOV / 2);
    t_position ray_position = find_horizontal_line(&(data->game), ray_angle);
    double wall_dist = get_wall_distance(ray_angle, ray_position, data->game.player.position);

    ASSERT_DBL_FAR(expected_dist, wall_dist);
}

CTEST2(wall_distance, player_facing_110_degrees)
{
    int expected_x = 1;
    int expected_y = 4;
    double expected_dist = 51.544;

    data->game.player.position.x = 48;
    data->game.player.position.y = 80;
    data->game.player.angle = 110;

    draw_map(data->game, expected_x, expected_y);

    double ray_angle = data->game.player.angle - (data->game.player.FOV / 2);
    t_position ray_position = find_horizontal_line(&(data->game), ray_angle);
    double wall_dist = get_wall_distance(ray_angle, ray_position, data->game.player.position);

    printf("%f\n", wall_dist);
    ASSERT_DBL_NEAR(expected_dist, wall_dist);
}