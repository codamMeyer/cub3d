#include "player.h"
#include <math.h>
#include <utils/math_utils.h>
#include <utils/math_utils2.h>

t_player create_player()
{
	t_player player;

	player.angle = INVALID_ORIENTATION;
	player.FOV = 60;
	player.speed = 10;
	return (player);
}

static t_bool can_move(t_map worldMap, t_position new_pos)
{
	const t_grid_position pos = to_grid_position(worldMap, new_pos);

	return (worldMap.matrix[pos.y][pos.x] == (int)EMPTY);
}

static t_bool move(t_player *player, t_map worldMap, t_position new_pos)
{
	if (!can_move(worldMap, new_pos))
		return (FALSE);
	player->position.y = new_pos.y;
	player->position.x = new_pos.x;
	return (TRUE);
}

t_bool move_left(t_player *player, t_map worldMap)
{
	const t_position new_pos = {
		.x = (player->position.x +
			  floor(cos(degree_to_radians(player->angle + 90)) * player->speed)),
		.y =
			player->position.y - floor(sin(degree_to_radians(player->angle + 90)) * player->speed)};

	return (move(player, worldMap, new_pos));
}

t_bool move_right(t_player *player, t_map worldMap)
{
	const t_position new_pos = {
		.x = player->position.x + floor(cos(degree_to_radians(player->angle - 90)) * player->speed),
		.y =
			player->position.y - floor(sin(degree_to_radians(player->angle - 90)) * player->speed)};

	return (move(player, worldMap, new_pos));
}

t_bool move_forward(t_player *player, t_map worldMap)
{
	const t_position new_pos = {
		.x = player->position.x + floor(cos(degree_to_radians(player->angle)) * player->speed),
		.y = player->position.y - floor(sin(degree_to_radians(player->angle)) * player->speed)};

	return (move(player, worldMap, new_pos));
}

t_bool move_backward(t_player *player, t_map worldMap)
{
	const t_position new_pos = {
		.x = player->position.x - floor(cos(degree_to_radians(player->angle)) * player->speed),
		.y = player->position.y + floor(sin(degree_to_radians(player->angle)) * player->speed)};

	return (move(player, worldMap, new_pos));
}

void turn_counterclockwise(t_player *player)
{
	player->angle = fix_angle(player->angle);
	player->angle += 2.0;
}

void turn_clockwise(t_player *player)
{
	player->angle = fix_angle(player->angle);
	player->angle -= 2.0;
}