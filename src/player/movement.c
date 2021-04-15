#include "movement.h"
#include <math.h>
#include <utils/angle_utils.h>
#include <utils/grid_position.h>

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
	return (is_valid_position(worldMap, new_pos) && worldMap.matrix[pos.y][pos.x] == (int)EMPTY);
}

static void	move(t_player *player, t_map worldMap, t_position new_pos)
{
	if (!can_move(worldMap, new_pos, player->position))
		return ;
	player->position.y = new_pos.y;
	player->position.x = new_pos.x;
	return ;
}

static double	get_increment_angle(double angle, t_direction direction)
{
	if (direction == FORWARD)
		return (angle);
	else if (direction == BACKWARD)
		return (angle);
	else if (direction == LEFT)
		return (angle + 90.0);
	else if (direction == RIGHT)
		return (angle - 90.0);
	else
		return (0);
}

static void	turn(t_player *player)
{
	player->angle = fix_angle(player->angle);
	player->angle += (player->rotation / 3.0);
}

void	update(t_player *player, t_map worldMap)
{
	const double		angle = \
			get_increment_angle(player->angle, player->direction);
	const t_position	dir = {
								.x = cos(degree_to_radians(angle)),
								.y = sin(degree_to_radians(angle)),
								};
	int					mov_x;
	int					mov_y;
	t_position			new_pos;

	turn(player);
	mov_x = floor(dir.x * player->speed);
	mov_y = floor(dir.y * player->speed);
	if (player->direction == STILL)
		return ;
	else if (player->direction == BACKWARD)
		mov_x *= -1;
	else
		mov_y *= -1;
	new_pos.x = player->position.x + mov_x;
	new_pos.y = player->position.y + mov_y;
	move(player, worldMap, new_pos);
}
