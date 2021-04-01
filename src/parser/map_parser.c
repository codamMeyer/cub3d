#include <gnl/get_next_line.h>
#include <libft.h>
#include <parser/map_parser.h>
#include <parser/utils_parser.h>
#include <stdio.h>
#include <utils/math_utils.h>

static t_player_orientation get_orientation(char c)
{
	if(c == 'N')
		return (N);
	else if(c == 'S')
		return (S);
	else if(c == 'W')
		return (W);
	else if(c == 'E')
		return (E);
	return (INVALID_ORIENTATION);
}

static t_status get_player_init_pos(int **matrix, int row, int col, t_player *player)
{
	t_grid_position pos;

	pos.x = col;
	pos.y = row;
	if(player->angle != (int)INVALID_ORIENTATION)
		return (PLAYER_INIT_ERROR);
	player->angle = (int)matrix[row][col];
	player->position = get_grid_center(pos);
	matrix[row][col] = 0;
	return (SUCCESS);
}

t_bool check_map_content(t_map *map, t_player *player)
{
	int i;
	int j;
	t_status ret;

	ret = SUCCESS;
	i = 0;
	while(i < map->height)
	{
		j = 0;
		while(j < map->width)
		{
			if(map->matrix[i][j] == INVALID)
				ret = MAP_CONTENT_ERROR;
			else if((i == 0 || i == map->height - 1) && map->matrix[i][j] != 1)
				ret = MAP_NOT_SURROUNDED_ERROR;
			else if((j == 0 || j == map->width - 1) && map->matrix[i][j] != 1)
				ret = MAP_NOT_SURROUNDED_ERROR;
			else if(map->matrix[i][j] > 2 || map->matrix[i][j] < 0)
				ret = get_player_init_pos(map->matrix, i, j, player);
			if(ret)
			{
				free_matrix(map->matrix, map->height);
				return (ret);
			}
			j++;
		}
		i++;
	}
	if(player->angle == (int)INVALID_ORIENTATION)
	{
		free_matrix(map->matrix, map->height);
		ret = PLAYER_INIT_ERROR;
	}
	return (ret);
}

t_status populate_map(const int fd, t_map *map, char **line)
{
	int i;
	int j;
	int bytes_read;
	char cur_char;
	int line_len;

	i = 0;
	while(TRUE)
	{
		j = 0;

		line_len = ft_strlen(*line);
		while(j < line_len)
		{
			cur_char = (*line)[j];
			if(is_wall(line, j))
				map->matrix[i][j] = WALL;
			else if(get_orientation(cur_char) != INVALID_ORIENTATION)
				map->matrix[i][j] = get_orientation(cur_char);
			else if(is_sprite(cur_char))
				map->matrix[i][j] = SPRITE;
			else if(cur_char == '0')
				map->matrix[i][j] = EMPTY;
			else
				map->matrix[i][j] = INVALID;
			++j;
		}
		while(j < map->width)
		{
			if(line_len > 0)
				map->matrix[i][j] = WALL;
			else
				map->matrix[i][j] = INVALID;
			++j;
		}
		++i;
		free(*line);
		bytes_read = get_next_line(fd, line);
		if(bytes_read < 0)
		{
			free_matrix(map->matrix, map->height);
			return (MALLOC_ERROR);
		}
		if(i == map->height)
			break;
	}
	free(*line);
	return (SUCCESS);
}

t_status get_map_dimentions(const int fd, char **line, t_map *map)
{
	int bytes_read;
	t_status ret;

	ret = SUCCESS;
	while(TRUE)
	{
		++(map->height);
		map->width = max_d(map->width, ft_strlen(*line));
		free(*line);
		bytes_read = get_next_line(fd, line);
		if(bytes_read < 0)
		{
			ret = MALLOC_ERROR;
			break;
		}
		if(bytes_read == 0)
		{
			if(ft_strlen(*line) > 0)
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
