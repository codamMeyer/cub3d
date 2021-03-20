#include <defs.h>
#include <map.h>
#include <math.h>
#include <math_utils.h>
#include <mlx.h>
#include <render.h>
#include <stdio.h>
#include <stdlib.h>
#include <utils.h>

int get_pixel_color(const t_texture *texture, int x, int y)
{
	const int bytes_per_pixel = 4;
	unsigned char *color_address;
	int color;
	int index;
	int i;
	color = BLACK;
	color_address = (unsigned char *)&color;

	if(x >= texture->width || y >= texture->height)
		return (color);
	if(x < 0 || y < 0)
		return (color);
	index = (x + y * texture->width) * bytes_per_pixel;
	i = 0;
	while(i < bytes_per_pixel)
	{
		color_address[i] = texture->data[index + i];
		++i;
	}
	return (color);
}

static void draw_ceiling_slice(t_data *data, int slice_col, int wall_top)
{
	int i = 0;
	while(i < wall_top)
	{
		my_mlx_pixel_put(&data->map, slice_col, i, SKY_COLOR);
		++i;
	}
}
static t_texture_position get_texture_position(const t_texture *texture,
											   const t_ray *ray,
											   t_dimentions wall_dimentions,
											   int wall_index)
{
	const double texture_to_wall_ratio = (double)texture->height / (double)wall_dimentions.height;
	const int wall_pixel_position = (wall_index - wall_dimentions.top);
	t_texture_position pos;
	pos.y = floor(wall_pixel_position * texture_to_wall_ratio);

	if(ray->orientation == HORIZONTAL)
		pos.x = (int)ray->pos.x % texture->width;
	else
		pos.x = (int)ray->pos.y % texture->width;

	return (pos);
}

static void draw_wall_slice(t_data *data, int slice_col, t_dimentions wall_dimentions, t_ray ray)
{
	int wall_index = wall_dimentions.top;
	int color;
	t_texture_position texture_pos;
	while(wall_index <= wall_dimentions.bottom)
	{
		texture_pos = get_texture_position(&data->texture, &ray, wall_dimentions, wall_index);
		color = get_pixel_color(&data->texture, texture_pos.x, texture_pos.y);
		my_mlx_pixel_put(&data->map, slice_col, wall_index, color);
		++wall_index;
	}
}

static void draw_floor_slice(t_data *data, int slice_col, int wall_bottom)
{
	int i = wall_bottom;
	while(i < data->player.plane_y)
	{
		my_mlx_pixel_put(&data->map, slice_col, i, DARK_BROWN);
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
	// t_collider obj_type = get_obj_type(data->worldMap, ray.pos);
	// int color = YELLOW;
	draw_ceiling_slice(data, slice_col, wall_dimentions.top);
	draw_wall_slice(data, slice_col, wall_dimentions, ray);
	draw_floor_slice(data, slice_col, wall_dimentions.bottom);
}