#include <math.h>
#include <math_utils.h>
#include <player.h>
#include <raycaster.h>
#include <utils.h>

static t_bool hit_wall(t_map worldMap, t_position new_pos)
{
	t_grid_position pos = to_grid_position(worldMap, new_pos);
	if (worldMap.matrix[pos.y][pos.x] > 0)
		return (TRUE);
	return (FALSE);
}
int draw_player(t_data *data)
{
	draw_square(&data->map,
				6,
				data->player.position.x - data->player.size / 2,
				data->player.position.y - data->player.size / 2,
				YELLOW);

	draw_square(&data->map, 2, data->player.position.x, data->player.position.y, RED);
	return (1);
}

void init_player(t_data *data)
{
	data->player.position.x = 48;
	data->player.position.y = 113;
	data->player.size = 5;
	data->player.FOV = 60;
	data->player.plane_x = 320;
	data->player.plane_y = 200;
	data->player.angle = 90;
	data->player.speed = 5;
	data->player.color = BLUE;
}

t_bool move_forward(t_player *player, t_data *data)
{
	t_position new_pos = player->position;
	new_pos.x += floor(cos(degree_to_radians(player->angle)) * player->speed);
	new_pos.y -= floor(sin(degree_to_radians(player->angle)) * player->speed);
	if (!hit_wall(data->worldMap, new_pos))
	{
		player->position.y = new_pos.y;
		player->position.x = new_pos.x;
		return (TRUE);
	}
	return (FALSE);
}

t_bool move_backward(t_player *player, t_data *data)
{
	t_position new_pos = player->position;
	new_pos.x -= floor(cos(degree_to_radians(player->angle)) * player->speed);
	new_pos.y += floor(sin(degree_to_radians(player->angle)) * player->speed);
	if (!hit_wall(data->worldMap, new_pos))
	{
		player->position.y = new_pos.y;
		player->position.x = new_pos.x;
		return (TRUE);
	}
	return (FALSE);
}

void turn_counterclockwise(t_player *player)
{
	if (player->angle >= 360)
		player->angle = 0;
	player->angle += 1.5;
}

void turn_clockwise(t_player *player)
{
	if (player->angle <= 0)
		player->angle = 360;
	player->angle -= 1.5;
}