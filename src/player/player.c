#include "player.h"
#include <math.h>
#include <utils/angle_utils.h>
#include <utils/math_utils.h>

t_player	create_player(void)
{
	const t_player	player = {
								.angle = INVALID_ORIENTATION,
								.FOV = 60,
								.speed = 10
							};

	return (player);
}

static t_bool	can_move(t_map worldMap,
						t_position new_pos,
						t_position prev_pos)
{
	const double		player_width = 4.0;
	const double		half_player_width = player_width / 2;
	const t_position	delta = {
									.x = new_pos.x - prev_pos.x,
									.y = new_pos.y - prev_pos.y
								};
	t_grid_position		pos;

	new_pos.x += half_player_width;
	new_pos.y += half_player_width;
	if (delta.x < 0)
		new_pos.x -= player_width;
	if (delta.y < 0)
		new_pos.y -= player_width;
	pos = to_grid_position(worldMap, new_pos);
	return (worldMap.matrix[pos.y][pos.x] == (int)EMPTY);
}

static t_bool	move(t_player *player, t_map worldMap, t_position new_pos)
{
	if (!can_move(worldMap, new_pos, player->position))
		return (FALSE);
	player->position.y = new_pos.y;
	player->position.x = new_pos.x;
	return (TRUE);
}

t_bool	move_left(t_player *player, t_map worldMap)
{
	const double		dir_x = cos(degree_to_radians(player->angle + 90));
	const double		dir_y = sin(degree_to_radians(player->angle + 90));
	const int			mov_x = floor(dir_x * player->speed);
	const int			mov_y = floor(dir_y * player->speed);
	const t_position	new_pos = {
									.x = (player->position.x + mov_x),
									.y = player->position.y - mov_y
								};

	return (move(player, worldMap, new_pos));
}

t_bool	move_right(t_player *player, t_map worldMap)
{
	const double		dir_x = cos(degree_to_radians(player->angle - 90));
	const double		dir_y = sin(degree_to_radians(player->angle - 90));
	const int			mov_x = floor(dir_x * player->speed);
	const int			mov_y = floor(dir_y * player->speed);
	const t_position	new_pos = {
									.x = (player->position.x + mov_x),
									.y = player->position.y - mov_y
								};

	return (move(player, worldMap, new_pos));
}

t_bool	move_forward(t_player *player, t_map worldMap)
{
	const double		dir_x = cos(degree_to_radians(player->angle));
	const double		dir_y = sin(degree_to_radians(player->angle));
	const int			mov_x = floor(dir_x * player->speed);
	const int			mov_y = floor(dir_y * player->speed);
	const t_position	new_pos = {
									.x = player->position.x + mov_x,
									.y = player->position.y - mov_y
								};

	return (move(player, worldMap, new_pos));
}

t_bool	move_backward(t_player *player, t_map worldMap)
{
	const double		dir_x = cos(degree_to_radians(player->angle));
	const double		dir_y = sin(degree_to_radians(player->angle));
	const int			mov_x = floor(dir_x * player->speed);
	const int			mov_y = floor(dir_y * player->speed);
	const t_position	new_pos = {
									.x = player->position.x - mov_x,
									.y = player->position.y + mov_y
								};

	return (move(player, worldMap, new_pos));
}

void	turn_counterclockwise(t_player *player)
{
	player->angle = fix_angle(player->angle);
	player->angle += 2.0;
}

void	turn_clockwise(t_player *player)
{
	player->angle = fix_angle(player->angle);
	player->angle -= 2.0;
}
