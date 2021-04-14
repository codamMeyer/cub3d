#include "map_parser_utils.h"
#include "utils_parser.h"
#include <errors/errors.h>

static t_player_orientation	get_orientation(char c)
{
	if (c == 'N')
		return (N);
	else if (c == 'S')
		return (S);
	else if (c == 'W')
		return (W);
	else if (c == 'E')
		return (E);
	return (INVALID_ORIENTATION);
}

static t_status	get_player_init_pos(int **matrix,
									t_grid_position pos,
									t_player *player)
{
	const t_grid_position	player_pos = pos;

	if (player->angle != (int)INVALID_ORIENTATION)
		return (PLAYER_INIT_ERROR);
	player->angle = (int)matrix[pos.y][pos.x];
	player->position = get_grid_center(player_pos);
	matrix[pos.y][pos.x] = 0;
	return (SUCCESS);
}

t_bool	is_player_initialized(t_map *map, t_player *player, t_grid_position pos)
{
	t_status	ret;

	ret = SUCCESS;
	if (map->matrix[pos.y][pos.x] != (int)WALL && \
		map->matrix[pos.y][pos.x] != (int)SPRITE && \
		map->matrix[pos.y][pos.x] != (int)EMPTY)
		ret = get_player_init_pos(map->matrix, pos, player);
	if (pos.y == map->height - 1 && pos.x == map->width - 1 && \
		player->angle == (int)INVALID_ORIENTATION)
		ret = PLAYER_INIT_ERROR;
	return (ret == SUCCESS);
}

void	fill_spaces(t_map *map, int i, int j, int line_len)
{
	while (j < map->width)
	{
		if (line_len > 0)
			map->matrix[i][j] = WALL;
		else
			map->matrix[i][j] = INVALID;
		++j;
	}
}

int	get_value(char c, char **line, int j, int *sprite_count)
{
	if (is_wall(line, j))
		return ((int)WALL);
	else if (get_orientation(c) != INVALID_ORIENTATION)
		return ((int)get_orientation(c));
	else if (c == '0')
		return ((int)EMPTY);
	else if (c == '2')
	{
		++(*sprite_count);
		return ((int)SPRITE);
	}
	else
		return (INVALID);
}
