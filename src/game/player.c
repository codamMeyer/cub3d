#include <game/player.h>
#include <math.h>
#include <utils/math_utils.h>

static t_bool hit_wall(t_map worldMap, t_position new_pos)
{
	t_grid_position pos = to_grid_position(worldMap, new_pos);
	if (worldMap.matrix[pos.y][pos.x] > 0)
		return (TRUE);
	return (FALSE);
}

void init_player(t_data *data)
{
	data->player.angle = INVALID_ORIENTATION;
	data->player.FOV = 60;
	data->screen.width = data->screen.width;
	data->screen.height = data->screen.height;
	data->player.speed = 10;
}

t_bool move_left(t_player *player, t_data *data)
{
	t_position new_pos = player->position;
	new_pos.x += floor(cos(degree_to_radians(player->angle + 90)) * player->speed);
	new_pos.y -= floor(sin(degree_to_radians(player->angle + 90)) * player->speed);
	if (!hit_wall(data->worldMap, new_pos))
	{
		player->position.y = new_pos.y;
		player->position.x = new_pos.x;
		return (TRUE);
	}
	return (FALSE);
}

t_bool move_right(t_player *player, t_data *data)
{
	t_position new_pos = player->position;
	new_pos.x += floor(cos(degree_to_radians(player->angle - 90)) * player->speed);
	new_pos.y -= floor(sin(degree_to_radians(player->angle - 90)) * player->speed);
	if (!hit_wall(data->worldMap, new_pos))
	{
		player->position.y = new_pos.y;
		player->position.x = new_pos.x;
		return (TRUE);
	}
	return (FALSE);
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
	player->angle += 2.0;
}

void turn_clockwise(t_player *player)
{
	if (player->angle <= 0)
		player->angle = 360;
	player->angle -= 2.0;
}