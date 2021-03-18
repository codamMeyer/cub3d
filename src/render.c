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

static int get_height(double closest_wall, double dist_to_plane, int max_height)
{
	int height = round((GRID_SIZE / closest_wall) * dist_to_plane);
	return (min_i(height, max_height));
}

static t_dimentions get_dimentions(double closest_wall, t_player player)
{
	const double dist_to_plane = (player.plane_x / 2.0) / tan(degree_to_radians(player.FOV / 2.0));
	t_dimentions dimentions;

	dimentions.height = get_height(closest_wall, dist_to_plane, player.plane_y);
	dimentions.top = round(((double)player.plane_y / 2.0) - (dimentions.height / 2.0));
	dimentions.bottom = dimentions.top + dimentions.height;

	return (dimentions);
}

t_collider get_obj_type(t_map worldmap, t_position pos)
{
	t_grid_position grid_pos = to_grid_position(worldmap, pos);

	return (worldmap.matrix[grid_pos.y][grid_pos.x]);
}

void draw_slice(t_data *data, int slice_col, t_ray ray)
{
	const t_dimentions wall_dimentions = get_dimentions(ray.distance, data->player);
	t_collider obj_type = get_obj_type(data->worldMap, ray.pos);
	int color = YELLOW;
	if(obj_type == wall)
	{
		if(ray.light)
			color = RED;
		else
			color = DARK_RED;
	}
	else if(obj_type == object)
	{
		if(ray.light)
			color = GREEN;
		else
			color = DARK_GREEN;
	}
	draw_ceiling_slice(data, slice_col, wall_dimentions.top);
	draw_wall_slice(data, slice_col, wall_dimentions.bottom, wall_dimentions.top, color);
	draw_floor_slice(data, slice_col, wall_dimentions.bottom);
}