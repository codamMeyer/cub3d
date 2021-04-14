#include "ctest.h"
#include <fcntl.h>
#include <libft.h>
#include <parser/parser.h>
#include <parser/texture_parser.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <utils/defs.h>
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
	data->filename = "./test/maps/resolution.cub";
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

	if (get_next_line(data->fd, &line))
	{
		ASSERT_EQUAL(SUCCESS, get_resolution(line, &data->actual_window));
		ASSERT_EQUAL(data->expected_window.width, data->actual_window.width);
		ASSERT_EQUAL(data->expected_window.height, data->actual_window.height);
		free(line);
	}
	// R 0 0 //
	data->expected_window.width = 0;
	data->expected_window.height = 0;

	if (get_next_line(data->fd, &line))
	{
		ASSERT_EQUAL(RESOLUTION_ERROR, get_resolution(line, &data->actual_window));
		ASSERT_EQUAL(data->expected_window.width, data->actual_window.width);
		ASSERT_EQUAL(data->expected_window.height, data->actual_window.height);
		free(line);
	}

	// R 1 0 //
	data->expected_window.width = 1;
	data->expected_window.height = 0;

	if (get_next_line(data->fd, &line))
	{
		ASSERT_EQUAL(RESOLUTION_ERROR, get_resolution(line, &data->actual_window));
		ASSERT_EQUAL(data->expected_window.width, data->actual_window.width);
		ASSERT_EQUAL(data->expected_window.height, data->actual_window.height);
		free(line);
	}

	// R           a //

	if (get_next_line(data->fd, &line))
	{
		ASSERT_EQUAL(RESOLUTION_ERROR, get_resolution(line, &data->actual_window));
		free(line);
	}

	// R -2 -8 //
	if (get_next_line(data->fd, &line))
	{
		ASSERT_EQUAL(RESOLUTION_ERROR, get_resolution(line, &data->actual_window));
		free(line);
	}

	// R A B //
	if (get_next_line(data->fd, &line))
	{
		ASSERT_EQUAL(RESOLUTION_ERROR, get_resolution(line, &data->actual_window));
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
	const char *filename = "./test/maps/textures.cub";
	t_texture textures[5] = {};
	const int fd = open(filename, O_RDONLY);
	char *line;
	int i = 0;
	while (i < 5)
	{
		get_next_line(fd, &line);
		ASSERT_EQUAL(SUCCESS, get_texture(line, textures));
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
	char *filename = "./test/maps/colors.cub";
	const int fd = open(filename, O_RDONLY);
	t_color floor = get_black_color();
	t_color celing = get_black_color();
	char *line = NULL;

	if (get_next_line(fd, &line))
	{
		ASSERT_EQUAL(SUCCESS, get_color(line, &floor));
		ASSERT_EQUAL(floor.opacity, 255);
		ASSERT_EQUAL(floor.red, 255);
		ASSERT_EQUAL(floor.green, 255);
		ASSERT_EQUAL(floor.blue, 255);
		free(line);
	}

	if (get_next_line(fd, &line))
	{
		ASSERT_EQUAL(SUCCESS, get_color(line, &celing));
		ASSERT_EQUAL(255, celing.opacity);
		ASSERT_EQUAL(255, celing.red);
		ASSERT_EQUAL(0, celing.green);
		ASSERT_EQUAL(55, celing.blue);
		free(line);
	}

	if (get_next_line(fd, &line))
	{
		ASSERT_EQUAL(COLOR_ERROR, get_color(line, &floor));
		free(line);
	}

	if (get_next_line(fd, &line))
	{
		ASSERT_EQUAL(COLOR_ERROR, get_color(line, &celing));
		free(line);
	}
	if (get_next_line(fd, &line))
	{
		ASSERT_EQUAL(SUCCESS, get_color(line, &floor));
		ASSERT_EQUAL(255, floor.opacity);
		ASSERT_EQUAL(30, floor.red);
		ASSERT_EQUAL(215, floor.green);
		ASSERT_EQUAL(96, floor.blue);
		free(line);
	}
}

CTEST(get_all, wrong_resolution)
{
	char *filename = "./test/maps/test_all_wrong.cub";
	t_data data;
	data.player.angle = (int)INVALID_ORIENTATION;
	ASSERT_EQUAL(RESOLUTION_ERROR, parse_input(filename, &data));
}

CTEST(check_file_extension, with_parser)
{
	t_data data;
	data.player.angle = (int)INVALID_ORIENTATION;
	ASSERT_EQUAL(SUCCESS, check_file_extension("map.cub"));
	ASSERT_EQUAL(EXTENSION_ERROR, check_file_extension("map.txt"));
	ASSERT_EQUAL(EXTENSION_ERROR, parse_input("map.txt", &data));
}

CTEST(parse_map, whole_map)
{
	t_map map;
	ASSERT_EQUAL(SUCCESS, parse_map("./test/maps/map.cub", &map));
	ASSERT_EQUAL(5, map.width);
	ASSERT_EQUAL(8, map.height);
}

CTEST(parse_map, no_map)
{
	t_map map;
	ASSERT_EQUAL(MISSING_MAP_ERROR, parse_map("./test/maps/colors.cub", &map));
}

CTEST(parse_map, map_with_spaces)
{
	t_map map;
	ASSERT_EQUAL(SUCCESS, parse_map("./test/maps/map_with_spaces.cub", &map));

	ASSERT_EQUAL(12, map.width);
	ASSERT_EQUAL(8, map.height);
}

CTEST(parse_map, matrix)
{
	t_map map;
	t_player player;
	player.angle = (int)INVALID_ORIENTATION;
	ASSERT_EQUAL(SUCCESS, parse_map("./test/maps/map_with_spaces.cub", &map));
	ASSERT_EQUAL(SUCCESS, init_map_matrix("./test/maps/map_with_spaces.cub", &map, &player));
	ASSERT_EQUAL(12, map.width);
	ASSERT_EQUAL(8, map.height);
	ASSERT_EQUAL(N, player.angle);
	t_grid_position pos = to_grid_position(map, player.position);
	ASSERT_EQUAL(6, pos.y);
	ASSERT_EQUAL(10, pos.x);
}

CTEST(parse_map, invalid_matrix)
{
	t_map map;
	t_player player;
	player.angle = (int)INVALID_ORIENTATION;
	ASSERT_EQUAL(SUCCESS, parse_map("./test/maps/wrong_map.cub", &map));
	ASSERT_EQUAL(MAP_NOT_SURROUNDED_ERROR,
				 init_map_matrix("./test/maps/wrong_map.cub", &map, &player));
	ASSERT_EQUAL(map.width, 12);
	ASSERT_EQUAL(map.height, 8);
}

CTEST(parse_map, invalid_matrix_empty_line)
{
	t_map map;
	t_player player;
	player.angle = (int)INVALID_ORIENTATION;
	ASSERT_EQUAL(SUCCESS, parse_map("./test/maps/invalid_map.cub", &map));
	ASSERT_EQUAL(MAP_CONTENT_ERROR, init_map_matrix("./test/maps/invalid_map.cub", &map, &player));
	ASSERT_EQUAL(map.width, 12);
	ASSERT_EQUAL(map.height, 9);
}

CTEST(parse_map, matrix_line_of_spaces)
{
	t_map map;
	t_player player;
	player.angle = (int)INVALID_ORIENTATION;
	ASSERT_EQUAL(SUCCESS, parse_map("./test/maps/weird_map.cub", &map));
	ASSERT_EQUAL(PLAYER_INIT_ERROR, init_map_matrix("./test/maps/weird_map.cub", &map, &player));
	ASSERT_EQUAL(12, map.width);
	ASSERT_EQUAL(9, map.height);
}

CTEST(parse_map, get_player_position_incorrect)
{
	t_map map;
	t_player player;
	player.angle = (int)INVALID_ORIENTATION;
	player.angle = INVALID_ORIENTATION;

	ASSERT_EQUAL(SUCCESS, parse_map("./test/maps/weird_map.cub", &map));
	ASSERT_EQUAL(PLAYER_INIT_ERROR, init_map_matrix("./test/maps/weird_map.cub", &map, &player));
	ASSERT_EQUAL(12, map.width);
	ASSERT_EQUAL(9, map.height);
}

CTEST(parse_map, wrong_chars_in_map)
{
	t_map map;
	t_player player;
	player.angle = (int)INVALID_ORIENTATION;
	player.angle = INVALID_ORIENTATION;

	ASSERT_EQUAL(SUCCESS, parse_map("./test/maps/map_with_wrong_chars.cub", &map));
	ASSERT_EQUAL(MAP_CONTENT_ERROR,
				 init_map_matrix("./test/maps/map_with_wrong_chars.cub", &map, &player));
	ASSERT_EQUAL(17, map.width);
	ASSERT_EQUAL(8, map.height);
}

CTEST(get_all, correct_file)
{
	char *filename = "./test/maps/test_all.cub";
	t_data data;
	data.player.angle = (int)INVALID_ORIENTATION;

	ASSERT_EQUAL(SUCCESS, parse_input(filename, &data));

	ASSERT_EQUAL(800, data.screen.width);
	ASSERT_EQUAL(600, data.screen.height);
	ASSERT_STR("./textures/NO.xpm", &(data.textures[NO].filename[0]));
	ASSERT_STR("./textures/SO.xpm", &(data.textures[SO].filename[0]));
	ASSERT_STR("./textures/WE.xpm", &(data.textures[WE].filename[0]));
	ASSERT_STR("./textures/EA.xpm", &(data.textures[EA].filename[0]));
	ASSERT_STR("./textures/S.xpm", &(data.textures[SP].filename[0]));
	ASSERT_EQUAL(255, data.floor.opacity);
	ASSERT_EQUAL(246, data.floor.red);
	ASSERT_EQUAL(208, data.floor.green);
	ASSERT_EQUAL(95, data.floor.blue);
	ASSERT_EQUAL(255, data.ceiling.opacity);
	ASSERT_EQUAL(191, data.ceiling.red);
	ASSERT_EQUAL(97, data.ceiling.green);
	ASSERT_EQUAL(106, data.ceiling.blue);
	ASSERT_EQUAL(2, data.worldMap.sprites_count);
	ASSERT_TRUE(NULL != data.sprites);
}