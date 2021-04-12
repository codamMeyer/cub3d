#include "map_parser.h"
#include <gnl/get_next_line.h>
#include <libft.h>
#include <parser/utils_parser.h>
#include <player/player.h>
#include <stdio.h>
#include <utils/angle_utils.h>
#include <utils/math_utils.h>

static t_player_orientation get_orientation(char c)
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

static t_status get_player_init_pos(int **matrix, t_grid_position pos, t_player *player)
{
	t_grid_position player_pos;

	player_pos = pos;
	if (player->angle != (int)INVALID_ORIENTATION)
		return (PLAYER_INIT_ERROR);
	player->angle = (int)matrix[pos.y][pos.x];
	player->position = get_grid_center(player_pos);
	matrix[pos.y][pos.x] = 0;
	return (SUCCESS);
}

t_bool is_surrounded_by_walls(t_map *map, t_grid_position pos)
{
	if ((pos.y == 0 || pos.y == map->height - 1) && map->matrix[pos.y][pos.x] != (int)WALL)
		return (FALSE);
	if ((pos.x == 0 || pos.x == map->width - 1) && map->matrix[pos.y][pos.x] != (int)WALL)
		return (FALSE);
	return (TRUE);
}

t_bool is_player_initialized(t_map *map, t_player *player, t_grid_position pos)
{
	t_status ret;

	ret = SUCCESS;
	if (map->matrix[pos.y][pos.x] != (int)WALL && map->matrix[pos.y][pos.x] != (int)SPRITE &&
		map->matrix[pos.y][pos.x] != (int)EMPTY)
		ret = get_player_init_pos(map->matrix, pos, player);
	if (pos.y == map->height - 1 && pos.x == map->width - 1 &&
		player->angle == (int)INVALID_ORIENTATION)
		ret = PLAYER_INIT_ERROR;
	return (ret == SUCCESS);
}

t_bool is_invalid(int i)
{
	return (i == INVALID);
}

t_status check_map_content(t_map *map, t_player *player)
{
	t_grid_position pos;
	t_status ret;

	ret = SUCCESS;
	pos.y = 0;
	while (pos.y < map->height && ret == SUCCESS)
	{
		pos.x = 0;
		while (pos.x < map->width && ret == SUCCESS)
		{
			if (is_invalid(map->matrix[pos.y][pos.x]))
				ret = MAP_CONTENT_ERROR;
			else if (!is_player_initialized(map, player, pos))
				ret = PLAYER_INIT_ERROR;
			else if (!is_surrounded_by_walls(map, pos))
				ret = MAP_NOT_SURROUNDED_ERROR;
			pos.x++;
		}
		pos.y++;
	}
	return (ret);
}

void fill_spaces(t_map *map, int i, int j, int line_len)
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

int get_value(char c, char **line, int j, int *sprite_count)
{
	if (is_wall(line, j))
		return ((int)WALL);
	else if (get_orientation(c) != INVALID_ORIENTATION)
		return ((int)get_orientation(c));
	else if (is_empty(c))
		return ((int)EMPTY);
	else if (is_sprite(c))
	{
		++(*sprite_count);
		return ((int)SPRITE);
	}
	else
		return (INVALID);
}

t_bool populate_map(const int fd, t_map *map, char **line)
{
	t_grid_position pos;
	int bytes_read;
	int line_len;

	map->sprites_count = 0;
	pos.y = 0;
	while (pos.y < map->height)
	{
		pos.x = 0;
		line_len = ft_strlen(*line);
		while (pos.x < line_len)
		{
			map->matrix[pos.y][pos.x] =
				get_value((*line)[pos.x], line, pos.x, &(map->sprites_count));
			++pos.x;
		}
		fill_spaces(map, pos.y, pos.x, line_len);
		free(*line);
		++pos.y;
		bytes_read = get_next_line(fd, line);
		if (bytes_read < 0)
			return (FALSE);
	}
	free(*line);
	return (TRUE);
}

t_status get_map_dimensions(const int fd, char **line, t_map *map)
{
	int bytes_read;
	t_status ret;

	ret = SUCCESS;
	while (ret == SUCCESS)
	{
		++(map->height);
		map->width = max_d(map->width, ft_strlen(*line));
		free(*line);
		bytes_read = get_next_line(fd, line);
		if (bytes_read < 0)
			ret = MALLOC_ERROR;
		if (bytes_read == 0)
		{
			if (ft_strlen(*line) > 0)
			{
				map->width = max_d(map->width, ft_strlen(*line));
				++(map->height);
			}
			free(*line);
			break;
		}
	}
	return (ret);
}
