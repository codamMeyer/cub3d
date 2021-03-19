#include <defs.h>
#include <map.h>
#include <math.h>
#include <math_utils.h>
#include <mlx.h>
#include <render.h>
#include <stdio.h>
#include <stdlib.h>
#include <utils.h>

void get_pixel_color(t_texture *texture, int x, int y, unsigned char *result)
{
	int index;
	int i;

	if(x >= texture->width || y >= texture->height)
		return;
	if(x < 0 || y < 0)
		return;
	index = (x + y * texture->width) * 4;
	i = -1;
	while(++i < 4)
		result[i] = texture->data[index + i];
}

static void draw_ceiling_slice(t_data *data, int slice_col, int wall_top)
{
	int i = 0;
	while(i < wall_top)
	{
		my_mlx_pixel_put(&data->map, slice_col, i, BLUE);
		++i;
	}
}

static void
draw_wall_slice(t_data *data, int slice_col, t_dimentions wall_dimentions, int color, t_ray ray)
{
	int i = wall_dimentions.top;
	// unsigned char test[5];
	unsigned char *addr = (unsigned char *)&color;
	while(i <= wall_dimentions.bottom)
	{

		const double ratio = data->texture->height / wall_dimentions.height;
		int wall_pixel = i - wall_dimentions.top;
		// printf("wall height: %d | i: %d  | slice_col: %d\n", wall_dimentions.height, i, slice_col);
		if(ray.light)
			get_pixel_color(
				data->texture, (int)ray.pos.x % data->texture->width, wall_pixel * ratio, addr);
		else
			get_pixel_color(
				data->texture, (int)ray.pos.y % data->texture->width, wall_pixel * ratio, addr);
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
		color = wall;
	else if(obj_type == object)
		color = RED;
	draw_ceiling_slice(data, slice_col, wall_dimentions.top);
	draw_wall_slice(data, slice_col, wall_dimentions, color, ray);
	draw_floor_slice(data, slice_col, wall_dimentions.bottom);
}