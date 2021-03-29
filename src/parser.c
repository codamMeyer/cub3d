#include <defs.h>
#include <fcntl.h>
#include <get_next_line.h>
#include <libft/libft.h>
#include <map.h>
#include <math_utils.h>
#include <parser.h>
#include <stdio.h>

static int num_of_strings(char **split)
{
	int i = 0;
	if(split == NULL)
		return (i);
	while(split[i] != NULL)
		++i;
	return (i);
}

static void free_split(char **split)
{
	int i = 0;
	while(split[i] != NULL)
	{
		free(split[i]);
		++i;
	}
	free(split);
}

static t_bool is_valid_color_range(unsigned char *colors)
{
	int i = 0;
	while(i < 3)
	{
		if(colors[i] < 0 || colors[i] > 255)
			return (FALSE);
		++i;
	}
	return (TRUE);
}

t_status get_color(const char *line, t_color *color)
{
	unsigned char *address = (unsigned char *)color;
	char **split = NULL;
	t_status ret = SUCCESS;

	split = ft_split(&line[1], ',');
	if(!split)
		return (MALLOC_ERROR);
	if(num_of_strings(split) == 3)
	{
		address[0] = ft_atoi(split[2]);
		address[1] = ft_atoi(split[1]);
		address[2] = ft_atoi(split[0]);
		address[3] = 0xff;
	}
	if(!is_valid_color_range(address))
		ret = COLOR_ERROR;
	free_split(split);
	return (ret);
}

t_texture_enum texture_to_enum(char *texture_type)
{
	if(ft_strncmp("NO", texture_type, 2) == 0)
		return (NO);
	else if(ft_strncmp("SO", texture_type, 2) == 0)
		return (SO);
	else if(ft_strncmp("WE", texture_type, 2) == 0)
		return (WE);
	else if(ft_strncmp("EA", texture_type, 2) == 0)
		return (EA);
	else
		return (SP);
}

t_status get_texture(const char *line, t_texture textures[])
{
	char **split = NULL;
	t_texture_enum text_index;
	t_status ret = TEXTURE_INFO_ERROR;

	split = ft_split(line, ' ');
	if(!split)
		return (MALLOC_ERROR);
	text_index = texture_to_enum(split[0]);
	if(num_of_strings(split) == 2 && text_index != INVALID_TEXTURE)
	{
		ft_strcpy(&(textures[text_index].filename[0]), split[1]);
		ret = SUCCESS;
	}
	free_split(split);
	return (ret);
}

t_bool is_texture(const char *line)
{
	if(ft_strncmp("NO", line, 2) == 0)
		return (TRUE);
	else if(ft_strncmp("SO", line, 2) == 0)
		return (TRUE);
	else if(ft_strncmp("WE", line, 2) == 0)
		return (TRUE);
	else if(ft_strncmp("EA", line, 2) == 0)
		return (TRUE);
	else if(ft_strncmp("S", line, 1) == 0)
		return (TRUE);
	return (FALSE);
}

t_status get_resolution(const char *line, t_window *window)
{
	char **split = NULL;
	t_status ret = RESOLUTION_ERROR;

	split = ft_split(line, ' ');
	if(!split)
		return (MALLOC_ERROR);
	if(num_of_strings(split) == 3)
	{
		window->width = ft_atoi(split[1]);
		window->height = ft_atoi(split[2]);
		if(window->width > 0 && window->height > 0)
			ret = SUCCESS;
	}
	free_split(split);
	return (ret);
}

t_status check_file_extension(const char *filename)
{
	const int len = ft_strlen(filename);

	if(ft_strncmp(&filename[len - 4], ".cub", 4) == 0)
		return (SUCCESS);
	return (EXTENSION_ERROR);
}

static t_bool is_map(const char *line)
{
	return (line[0] != '\0' && line[0] != 'R' && line[0] != 'F' && line[0] != 'C' &&
			!is_texture(line));
}

t_bool find_first_line_of_map(const int fd, char **line)
{
	while(get_next_line(fd, line))
	{
		if(is_map(*line))
			return (TRUE);
		free(*line);
	}
	return (FALSE);
}

t_status get_map_dimentions(const int fd, char **line, t_map *map)
{
	int bytes_read;
	while(TRUE)
	{
		++(map->height);
		map->width = max_d(map->width, ft_strlen(*line));
		free(*line);
		bytes_read = get_next_line(fd, line);
		if(bytes_read < 0)
			return (MALLOC_ERROR);
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
	return (SUCCESS);
}

t_bool is_player_orientation(char c)
{
	return (c == 'N' || c == 'S' || c == 'W' || c == 'E');
}

t_player_orientation get_orientation(char c)
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

t_bool is_wall(char **line, int i)
{
	const int line_len = ft_strlen(*line);
	const char cur_char = (*line)[i];

	return (i >= line_len || cur_char == ' ' || cur_char == '1');
}
t_bool is_sprite(char cur)
{
	return (cur == '2');
}
t_status populate_map(const int fd, t_map *map, char **line)
{
	int i;
	int j;
	int bytes_read;
	char cur_char;

	i = 0;
	while(TRUE)
	{
		j = 0;
		cur_char = (*line)[j];
		while(j < map->width)
		{
			if(is_wall(line, j))
				map->matrix[i][j] = WALL;
			else if(is_player_orientation(cur_char))
				map->matrix[i][j] = get_orientation(cur_char);
			else if(is_sprite(cur_char))
				map->matrix[i][j] = SPRITE;
			else if(cur_char == '0')
				map->matrix[i][j] = EMPTY;
			else
				map->matrix[i][j] = INVALID;
			j++;
			cur_char = (*line)[j];
		}
		i++;
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

t_status get_player_init_pos(int **matrix, int row, int col, t_player *player)
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

t_status init_map_matrix(const int fd, t_map *map, t_player *player)
{

	char *line;
	t_status ret;

	if(fd < 0)
		return (FILE_ERROR);
	find_first_line_of_map(fd, &line);
	map->matrix = malloc_matrix(map->height, map->width);
	if(!map->matrix)
		return (MALLOC_ERROR);
	else if((ret = populate_map(fd, map, &line)))
		return (ret);
	else if((ret = check_map_content(map, player)))
		return (ret);
	return (SUCCESS);
}

t_status parse_map(const int fd, t_map *map)
{
	char *line = NULL;

	map->height = 0;
	map->width = 0;
	if(!find_first_line_of_map(fd, &line))
	{
		free(line);
		return (MISSING_MAP_ERROR);
	}
	return (get_map_dimentions(fd, &line, map));
}

static t_status get_header_information(const int fd,
									   t_window *window,
									   t_texture textures[],
									   t_color *floor,
									   t_color *ceiling)
{
	char *line;
	t_status ret = SUCCESS;
	while(get_next_line(fd, &line))
	{
		if(line[0] == 'R')
			ret = get_resolution(line, window);
		else if(is_texture(line))
			ret = get_texture(line, textures);
		else if(line[0] == 'F')
			ret = get_color(line, floor);
		else if(line[0] == 'C')
			ret = get_color(line, ceiling);
		if(ret != SUCCESS)
			break;
		free(line);
	}
	free(line);
	return (ret);
}

t_status parse_input(const char *filename, t_data *data)
{
	const int fd1 = open(filename, O_RDONLY);
	const int fd2 = open(filename, O_RDONLY);
	const int fd3 = open(filename, O_RDONLY);
	t_status ret;
	ret = SUCCESS;

	if(fd1 < 0 || fd2 < 0 || fd3 < 0)
		return (FILE_ERROR);
	else if((ret = check_file_extension(filename)))
		return (ret);
	else if((ret = get_header_information(
				 fd1, &data->resolution, data->textures, &data->floor, &data->ceiling)))
		return (ret);
	else if((ret = parse_map(fd2, &data->worldMap)))
		return (ret);
	else if((ret = init_map_matrix(fd3, &data->worldMap, &data->player)))
		return (ret);
	close(fd1);
	close(fd2);
	close(fd3);
	return (ret);
}