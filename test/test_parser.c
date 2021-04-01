#include "ctest.h"
#include <fcntl.h>
#include <inc/gnl/get_next_line.h>
#include <inc/parser/parser.h>
#include <inc/parser/texture_parser.h>
#include <inc/utils/defs.h>
#include <libft.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <utils/math_utils.h>

CTEST_DATA(get_resolution)
{
	const char *filename;
	int fd;
	t_window actual_window;
	t_window expected_window;
};

CTEST_SETUP(get_resolution)
{
	data->filename = "./maps/resolution.cub";
	data->fd = open(data->filename, O_RDONLY);
}

CTEST_TEARDOWN(get_resolution)
{
	(void)data;
}

CTEST2(get_resolution, test_resolution_file)
{
	// R 800 600 //
	data->expected_window.width = 800;
	data->expected_window.height = 600;
	char *line;

	if(get_next_line(data->fd, &line))
	{
		ASSERT_EQUAL(get_resolution(line, &data->actual_window), SUCCESS);
		ASSERT_EQUAL(data->expected_window.width, data->actual_window.width);
		ASSERT_EQUAL(data->expected_window.height, data->actual_window.height);
		free(line);
	}
	// R 0 0 //
	data->expected_window.width = 0;
	data->expected_window.height = 0;

	if(get_next_line(data->fd, &line))
	{
		ASSERT_EQUAL(get_resolution(line, &data->actual_window), RESOLUTION_ERROR);
		ASSERT_EQUAL(data->expected_window.width, data->actual_window.width);
		ASSERT_EQUAL(data->expected_window.height, data->actual_window.height);
		free(line);
	}

	// R 1 0 //
	data->expected_window.width = 1;
	data->expected_window.height = 0;

	if(get_next_line(data->fd, &line))
	{
		ASSERT_EQUAL(get_resolution(line, &data->actual_window), RESOLUTION_ERROR);
		ASSERT_EQUAL(data->expected_window.width, data->actual_window.width);
		ASSERT_EQUAL(data->expected_window.height, data->actual_window.height);
		free(line);
	}

	// R           a //

	if(get_next_line(data->fd, &line))
	{
		ASSERT_EQUAL(get_resolution(line, &data->actual_window), RESOLUTION_ERROR);
		free(line);
	}

	// R -2 -8 //
	if(get_next_line(data->fd, &line))
	{
		ASSERT_EQUAL(get_resolution(line, &data->actual_window), RESOLUTION_ERROR);
		free(line);
	}

	// R A B //
	if(get_next_line(data->fd, &line))
	{
		ASSERT_EQUAL(get_resolution(line, &data->actual_window), RESOLUTION_ERROR);
		free(line);
	}
}

CTEST(get_textures_indexing_value, all)
{
	ASSERT_EQUAL(NO, texture_to_enum("NO"));
	ASSERT_EQUAL(SO, texture_to_enum("SO"));
	ASSERT_EQUAL(WE, texture_to_enum("WE"));
	ASSERT_EQUAL(EA, texture_to_enum("EA"));
	ASSERT_EQUAL(SP, texture_to_enum("S"));
}

CTEST(get_textures, test_correct_file)
{
	const char *filename = "./maps/textures.cub";
	t_texture textures[5] = {};
	const int fd = open(filename, O_RDONLY);
	char *line;
	int i = 0;
	while(i < 5)
	{
		get_next_line(fd, &line);
		ASSERT_EQUAL(get_texture(line, textures), SUCCESS);
		free(line);
		i++;
	}
	ASSERT_STR("./textures/NO.xpm", &(textures[NO].filename[0]));
	ASSERT_STR("./textures/SO.xpm", &(textures[SO].filename[0]));
	ASSERT_STR("./textures/WE.xpm", &(textures[WE].filename[0]));
	ASSERT_STR("./textures/EA.xpm", &(textures[EA].filename[0]));
	ASSERT_STR("./textures/S.xpm", &(textures[SP].filename[0]));
}

CTEST(get_colors, correct_file)
{
	char *filename = "./maps/colors.cub";
	const int fd = open(filename, O_RDONLY);
	t_color floor = 0;
	t_color celing = 0;
	char *line = NULL;

	if(get_next_line(fd, &line))
	{
		ASSERT_EQUAL(get_color(line, &floor), SUCCESS);
		ASSERT_EQUAL(floor, 0xFFFFFFFF);
		free(line);
	}

	if(get_next_line(fd, &line))
	{
		ASSERT_EQUAL(get_color(line, &celing), SUCCESS);
		ASSERT_EQUAL(celing, 0xFFFF0037);
		free(line);
	}

	if(get_next_line(fd, &line))
	{
		ASSERT_FALSE(get_color(line, &floor));
		free(line);
	}

	if(get_next_line(fd, &line))
	{
		ASSERT_FALSE(get_color(line, &celing));
		free(line);
	}
	if(get_next_line(fd, &line))
	{
		ASSERT_EQUAL(get_color(line, &floor), SUCCESS);
		ASSERT_EQUAL(floor, 0xFF1ED760);
		free(line);
	}
}

CTEST(get_all, wrong_resolution)
{
	char *filename = "./maps/test_all_wrong.cub";
	t_data data;
	data.player.angle = (int)INVALID_ORIENTATION;
	ASSERT_EQUAL(parse_input(filename, &data), RESOLUTION_ERROR);
}

CTEST(check_file_extension, with_parser)
{
	t_data data;
	data.player.angle = (int)INVALID_ORIENTATION;
	ASSERT_EQUAL(check_file_extension("map.cub"), SUCCESS);
	ASSERT_EQUAL(check_file_extension("map.txt"), EXTENSION_ERROR);
	ASSERT_EQUAL(parse_input("map.txt", &data), EXTENSION_ERROR);
}

CTEST(parse_map, whole_map)
{
	t_map map;
	ASSERT_EQUAL(parse_map("./maps/map.cub", &map), SUCCESS);
	ASSERT_EQUAL(map.width, 5);
	ASSERT_EQUAL(map.height, 8);
}

CTEST(parse_map, no_map)
{
	t_map map;
	ASSERT_EQUAL(parse_map("./maps/colors.cub", &map), MISSING_MAP_ERROR);
}

CTEST(parse_map, map_with_spaces)
{
	t_map map;
	ASSERT_EQUAL(parse_map("./maps/map_with_spaces.cub", &map), SUCCESS);

	ASSERT_EQUAL(map.width, 12);
	ASSERT_EQUAL(map.height, 8);
}

CTEST(parse_map, matrix)
{
	t_map map;
	t_player player;
	player.angle = (int)INVALID_ORIENTATION;
	ASSERT_EQUAL(parse_map("./maps/map_with_spaces.cub", &map), SUCCESS);
	ASSERT_EQUAL(init_map_matrix("./maps/map_with_spaces.cub", &map, &player), SUCCESS);
	ASSERT_EQUAL(map.width, 12);
	ASSERT_EQUAL(map.height, 8);
	ASSERT_EQUAL(player.angle, N);
	t_grid_position pos = to_grid_position(map, player.position);
	ASSERT_EQUAL(pos.y, 6);
	ASSERT_EQUAL(pos.x, 10);
}

CTEST(parse_map, invalid_matrix)
{
	t_map map;
	t_player player;
	player.angle = (int)INVALID_ORIENTATION;
	ASSERT_EQUAL(parse_map("./maps/wrong_map.cub", &map), SUCCESS);
	ASSERT_EQUAL(init_map_matrix("./maps/wrong_map.cub", &map, &player), MAP_NOT_SURROUNDED_ERROR);
	ASSERT_EQUAL(map.width, 12);
	ASSERT_EQUAL(map.height, 8);
}

CTEST(parse_map, invalid_matrix_empty_line)
{
	t_map map;
	t_player player;
	player.angle = (int)INVALID_ORIENTATION;
	ASSERT_EQUAL(parse_map("./maps/invalid_map.cub", &map), SUCCESS);
	ASSERT_EQUAL(init_map_matrix("./maps/invalid_map.cub", &map, &player), MAP_CONTENT_ERROR);
	ASSERT_EQUAL(map.width, 12);
	ASSERT_EQUAL(map.height, 9);
}

CTEST(parse_map, matrix_line_of_spaces)
{
	t_map map;
	t_player player;
	player.angle = (int)INVALID_ORIENTATION;
	ASSERT_EQUAL(parse_map("./maps/weird_map.cub", &map), SUCCESS);
	ASSERT_EQUAL(init_map_matrix("./maps/weird_map.cub", &map, &player), PLAYER_INIT_ERROR);
	ASSERT_EQUAL(map.width, 12);
	ASSERT_EQUAL(map.height, 9);
}

CTEST(parse_map, get_player_position_incorrect)
{
	t_map map;
	t_player player;
	player.angle = (int)INVALID_ORIENTATION;
	player.angle = INVALID_ORIENTATION;

	ASSERT_EQUAL(parse_map("./maps/weird_map.cub", &map), SUCCESS);
	ASSERT_EQUAL(init_map_matrix("./maps/weird_map.cub", &map, &player), PLAYER_INIT_ERROR);
	ASSERT_EQUAL(map.width, 12);
	ASSERT_EQUAL(map.height, 9);
}

CTEST(parse_map, wrong_chars_in_map)
{
	t_map map;
	t_player player;
	player.angle = (int)INVALID_ORIENTATION;
	player.angle = INVALID_ORIENTATION;

	ASSERT_EQUAL(parse_map("./maps/map_with_wrong_chars.cub", &map), SUCCESS);
	ASSERT_EQUAL(init_map_matrix("./maps/map_with_wrong_chars.cub", &map, &player), MAP_CONTENT_ERROR);
	ASSERT_EQUAL(map.width, 17);
	ASSERT_EQUAL(map.height, 8);
}


CTEST(get_all, correct_file)
{
	char *filename = "./maps/test_all.cub";

	t_data data;
	data.player.angle = (int)INVALID_ORIENTATION;

	ASSERT_EQUAL(parse_input(filename, &data), SUCCESS);

	ASSERT_EQUAL(800, data.screen.width);
	ASSERT_EQUAL(600, data.screen.height);
	ASSERT_STR("./textures/NO.xpm", &(data.textures[NO].filename[0]));
	ASSERT_STR("./textures/SO.xpm", &(data.textures[SO].filename[0]));
	ASSERT_STR("./textures/WE.xpm", &(data.textures[WE].filename[0]));
	ASSERT_STR("./textures/EA.xpm", &(data.textures[EA].filename[0]));
	ASSERT_STR("./textures/S.xpm", &(data.textures[SP].filename[0]));
	ASSERT_EQUAL(data.floor, 0xFFF6D05F);
	ASSERT_EQUAL(data.ceiling, 0xFFBF616A);
}