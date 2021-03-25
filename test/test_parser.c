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

	ASSERT_TRUE(get_resolution(data->fd, &data->actual_window));
	ASSERT_EQUAL(data->expected_window.width, data->actual_window.width);
	ASSERT_EQUAL(data->expected_window.height, data->actual_window.height);

	// R 0 0 //
	data->expected_window.width = 0;
	data->expected_window.height = 0;

	ASSERT_FALSE(get_resolution(data->fd, &data->actual_window));
	ASSERT_EQUAL(data->expected_window.width, data->actual_window.width);
	ASSERT_EQUAL(data->expected_window.height, data->actual_window.height);

	// R 1 0 //
	data->expected_window.width = 1;
	data->expected_window.height = 0;

	ASSERT_FALSE(get_resolution(data->fd, &data->actual_window));
	ASSERT_EQUAL(data->expected_window.width, data->actual_window.width);
	ASSERT_EQUAL(data->expected_window.height, data->actual_window.height);

	// R           a //
	ASSERT_FALSE(get_resolution(data->fd, &data->actual_window));

	// A  600 600 //
	ASSERT_FALSE(get_resolution(data->fd, &data->actual_window));

	// R -2 -8 //
	ASSERT_FALSE(get_resolution(data->fd, &data->actual_window));

	// R A B //
	ASSERT_FALSE(get_resolution(data->fd, &data->actual_window));
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

CTEST_DATA(get_textures)
{
	t_texture expected_textures[5];
	t_texture actual_textures[5];
};

CTEST_SETUP(get_textures)
{
	data->expected_textures[NO].filename = "./textures/NO.xpm";
	data->expected_textures[SO].filename = "./textures/SO.xpm";
	data->expected_textures[WE].filename = "./textures/WE.xpm";
	data->expected_textures[EA].filename = "./textures/EA.xpm";
	data->expected_textures[S].filename = "./textures/S.xpm";
}

CTEST_TEARDOWN(get_textures)
{
	(void)data;
}

CTEST2(get_textures, test_correct_file)
{
	char *filename = "./maps/textures.cub";
	const int fd = open(filename, O_RDONLY);

	ASSERT_TRUE(get_textures(fd, data->actual_textures));

	for(int i = 0; i < 5; ++i)
		ASSERT_STR(data->expected_textures[i].filename, data->actual_textures[i].filename);
}

CTEST2(get_textures, test_correct_file_with_empty_lines)
{
	char *filename = "./maps/textures_empty_lines.cub";
	const int fd = open(filename, O_RDONLY);

	ASSERT_TRUE(get_textures(fd, data->actual_textures));

	for(int i = 0; i < 5; ++i)
		ASSERT_STR(data->expected_textures[i].filename, data->actual_textures[i].filename);
}

CTEST2(get_textures, test_wrong_num_of_textures)
{
	char *filename = "./maps/textures_wrong_num.cub";
	const int fd = open(filename, O_RDONLY);

	ASSERT_FALSE(get_textures(fd, data->actual_textures));
}

CTEST(get_colors, correct_file)
{
	char *filename = "./maps/colors.cub";
	const int fd = open(filename, O_RDONLY);
	t_color floor = 0;
	t_color celing = 0;

	ASSERT_TRUE(get_surface_color(fd, &floor, 'F'));
	ASSERT_TRUE(get_surface_color(fd, &celing, 'C'));
	ASSERT_EQUAL(floor, 0xFFFFFFFF);
	ASSERT_EQUAL(celing, 0xFFFF0037);
	ASSERT_FALSE(get_surface_color(fd, &floor, 'F'));
	ASSERT_FALSE(get_surface_color(fd, &celing, 'C'));
}