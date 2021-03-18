#include <defs.h>
#include <map.h>
#include <math.h>
#include <math_utils.h>
#include <render.h>
#include <stdio.h>
#include <utils.h>

static void draw_ceiling_slice(t_data *data, int slice_col, int wall_top)
{
	int i = 0;
	while(i < wall_top)
	{
		my_mlx_pixel_put(&data->map, slice_col, i, BLUE);
		++i;
	}
}

static void draw_wall_slice(t_data *data, int slice_col, int wall_bottom, int wall_top, int color)
{
	int i = wall_top;
	while(i <= wall_bottom)
	{

		my_mlx_pixel_put(&data->map, slice_col, i, color);
		++i;
	}
}

static void draw_floor_slice(t_data *data, int slice_col, int wall_bottom)
{
	int i = wall_bottom;
	while(i < data->player.plane_y)
	{
		my_mlx_pixel_put(&data->map, slice_col, i, DARK_BLUE);
		++i;
	}
}

void draw_slice(t_data *data, double dist, int slice_col, int color)
{
	const double dist_to_plane =
		(data->player.plane_x / 2.0) / tan(degree_to_radians(data->player.FOV / 2.0));
	int wall_height = round((GRID_SIZE / dist) * dist_to_plane);
	wall_height = min_d(wall_height, data->player.plane_y);
	const int wall_top = round(((double)data->player.plane_y / 2.0) - (wall_height / 2.0));
	const int wall_bottom = wall_top + wall_height;
	draw_ceiling_slice(data, slice_col, wall_top);
	draw_wall_slice(data, slice_col, wall_bottom, wall_top, color);
	draw_floor_slice(data, slice_col, wall_bottom);
}