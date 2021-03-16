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

static void draw_wall_slice(t_data *data, int slice_col, int wall_bottom, int wall_top)
{
	int i = wall_top;
	while(i <= wall_bottom)
	{
		if(slice_col >= 14 && slice_col <= 23)
			my_mlx_pixel_put(&data->map, slice_col, i, GREEN);
		else
			my_mlx_pixel_put(&data->map, slice_col, i, RED);
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

void draw_slice(t_data *data, double dist, int slice_col)
{
	const double dist_to_plane =
		(data->player.plane_x / 2.0) / tan(degree_to_radians(data->player.FOV / 2.0));
	double wall_height = (GRID_SIZE / dist) * dist_to_plane;
	wall_height = min_d(wall_height, data->player.plane_y);
	const double wall_top = (data->player.plane_y / 2.0) - (wall_height / 2.0);
	const double wall_bottom = wall_top + wall_height;
	if(slice_col >= 14 && slice_col <= 23)
		printf("col: %d  | wall height: %f  |  wall top: %f\n", slice_col, wall_height, wall_top);
	draw_ceiling_slice(data, slice_col, wall_top);
	draw_wall_slice(data, slice_col, wall_bottom, wall_top);
	draw_floor_slice(data, slice_col, wall_bottom);
}