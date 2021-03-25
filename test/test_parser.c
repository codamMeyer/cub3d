#include "ctest.h"
#include <fcntl.h>
#include <inc/defs.h>
#include <inc/get_next_line.h>
#include <inc/parser.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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
		ASSERT_TRUE(get_resolution(line, &data->actual_window));
		ASSERT_EQUAL(data->expected_window.width, data->actual_window.width);
		ASSERT_EQUAL(data->expected_window.height, data->actual_window.height);
		free(line);
	}
	// R 0 0 //
	data->expected_window.width = 0;
	data->expected_window.height = 0;

	if(get_next_line(data->fd, &line))
	{
		ASSERT_FALSE(get_resolution(line, &data->actual_window));
		ASSERT_EQUAL(data->expected_window.width, data->actual_window.width);
		ASSERT_EQUAL(data->expected_window.height, data->actual_window.height);
		free(line);
	}

	// R 1 0 //
	data->expected_window.width = 1;
	data->expected_window.height = 0;

	if(get_next_line(data->fd, &line))
	{
		ASSERT_FALSE(get_resolution(line, &data->actual_window));
		ASSERT_EQUAL(data->expected_window.width, data->actual_window.width);
		ASSERT_EQUAL(data->expected_window.height, data->actual_window.height);
		free(line);
	}

	// R           a //

	if(get_next_line(data->fd, &line))
	{
		ASSERT_FALSE(get_resolution(line, &data->actual_window));
		free(line);
	}

	// R -2 -8 //
	if(get_next_line(data->fd, &line))
	{
		ASSERT_FALSE(get_resolution(line, &data->actual_window));
		free(line);
	}

	// R A B //
	if(get_next_line(data->fd, &line))
	{
		ASSERT_FALSE(get_resolution(line, &data->actual_window));
		free(line);
	}
}

CTEST(get_textures_indexing_value, all)
{
	ASSERT_EQUAL(NO, texture_to_enum("NO"));
	ASSERT_EQUAL(SO, texture_to_enum("SO"));
	ASSERT_EQUAL(WE, texture_to_enum("WE"));
	ASSERT_EQUAL(EA, texture_to_enum("EA"));
	ASSERT_EQUAL(S, texture_to_enum("S"));
	ASSERT_EQUAL(INVAL, texture_to_enum("A"));
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
		ASSERT_TRUE(get_texture(line, textures));
		free(line);
		i++;
	}
	ASSERT_STR("./textures/NO.xpm", &(textures[NO].filename[0]));
	ASSERT_STR("./textures/SO.xpm", &(textures[SO].filename[0]));
	ASSERT_STR("./textures/WE.xpm", &(textures[WE].filename[0]));
	ASSERT_STR("./textures/EA.xpm", &(textures[EA].filename[0]));
	ASSERT_STR("./textures/S.xpm", &(textures[S].filename[0]));
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
		ASSERT_TRUE(get_color(line, &floor));
		ASSERT_EQUAL(floor, 0xFFFFFFFF);
		free(line);
	}

	if(get_next_line(fd, &line))
	{
		ASSERT_TRUE(get_color(line, &celing));
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
}

CTEST(get_all, correct_file)
{
	char *filename = "./maps/test_all.cub";

	t_window window;
	t_texture textures[5] = {};
	t_color floor = 0;
	t_color ceiling = 0;

	ASSERT_TRUE(parse_input(filename, &window, textures, &floor, &ceiling));

	ASSERT_EQUAL(800, window.width);
	ASSERT_EQUAL(600, window.height);
	ASSERT_STR("./textures/NO.xpm", &(textures[NO].filename[0]));
	ASSERT_STR("./textures/SO.xpm", &(textures[SO].filename[0]));
	ASSERT_STR("./textures/WE.xpm", &(textures[WE].filename[0]));
	ASSERT_STR("./textures/EA.xpm", &(textures[EA].filename[0]));
	ASSERT_STR("./textures/S.xpm", &(textures[S].filename[0]));

	ASSERT_EQUAL(floor, 0xFFF6D05F);
	ASSERT_EQUAL(ceiling, 0xFFBF616A);
}

CTEST(get_all, wrong_resolution)
{
	char *filename = "./maps/test_all_wrong.cub";

	t_window window;
	t_texture textures[5] = {};
	t_color floor = 0;
	t_color ceiling = 0;

	ASSERT_FALSE(parse_input(filename, &window, textures, &floor, &ceiling));
}