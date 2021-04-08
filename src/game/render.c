#include <game/render.h>
#include <math.h>
#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>
#include <utils/defs.h>
#include <utils/direction.h>
#include <utils/map_utils.h>
#include <utils/math_utils.h>
#include <utils/utils.h>

t_color get_pixel_color(const t_texture *texture, int x, int y)
{
	const int bytes_per_pixel = 4;
	unsigned char *color_address;
	t_color color;
	int index;
	int i;
	color = BLACK;
	color_address = (unsigned char *)&color;
	if (x >= texture->width || y >= texture->height)
		return (color);
	if (x < 0 || y < 0)
		return (color);
	index = (x + y * texture->width) * bytes_per_pixel;
	i = 0;
	while (i < bytes_per_pixel)
	{
		color_address[i] = texture->data[index + i];
		++i;
	}
	return (color);
}

static void draw_ceiling_slice(t_data *data, int slice_col, int wall_top, int wall_height)
{
	int i = 0;
	while (i < wall_top + (wall_height / 2))
	{
		my_mlx_pixel_put(&data->img, slice_col, i, data->ceiling);
		++i;
	}
}
static t_texture_position get_texture_position(const t_texture *texture,
											   const t_ray *ray,
											   t_dimensions wall_dimensions,
											   int wall_index)
{
	const double texture_to_wall_ratio =
		(double)texture->height / (double)wall_dimensions.real_height;

	const int wall_pixel_position = (wall_index - wall_dimensions.real_top);
	t_texture_position pos;

	pos.y = floor(wall_pixel_position * texture_to_wall_ratio);

	if (ray->orientation == HORIZONTAL)
		pos.x = (int)ray->pos.x % texture->width;
	else
		pos.x = (int)ray->pos.y % texture->width;
	return (pos);
}

t_color apply_shading(double distance, t_color color)
{
	t_color shade;
	unsigned char *address_shade;
	unsigned char *address_color;
	int i;

	address_shade = (unsigned char *)&shade;
	address_color = (unsigned char *)&color;

	if (distance <= 400 || color == BLACK)
		return (color);
	i = 0;
	while (i < 3)
	{
		address_shade[i] = address_color[i] * 0.3;
		++i;
	}
	return (shade);
}

static void draw_wall_slice(t_data *data,
							int slice_col,
							t_dimensions wall_dimensions,
							t_ray *ray,
							t_texture_enum texture)
{
	int wall_index = wall_dimensions.top;
	t_color color;
	t_texture_position texture_pos;
	while (wall_index <= wall_dimensions.bottom)
	{
		texture_pos =
			get_texture_position(&data->textures[texture], ray, wall_dimensions, wall_index);
		color = get_pixel_color(&data->textures[texture], texture_pos.x, texture_pos.y);
		color = apply_shading(ray->distance, color);
		if ((unsigned int)color != BLACK)
			my_mlx_pixel_put(&data->img, slice_col, wall_index, color);
		++wall_index;
	}
}

static void draw_floor_slice(t_data *data, int slice_col, int wall_bottom, int wall_height)
{
	int i = wall_bottom - (wall_height / 2);
	while (i < data->screen.height)
	{
		my_mlx_pixel_put(&data->img, slice_col, i, data->floor);
		++i;
	}
}

t_dimensions get_dimensions(double dist_to_wall, t_player player, t_window screen)
{
	
	t_dimensions dimensions;

	dimensions.real_height = round((GRID_SIZE / dist_to_wall) * player.dist_to_plane);
	dimensions.real_width = round((GRID_SIZE / dist_to_wall) * player.dist_to_plane);
	dimensions.height = min_i(dimensions.real_height, screen.height);
	dimensions.width = min_i(dimensions.real_width, screen.width);
	dimensions.top = round(((double)screen.height / 2.0) - (dimensions.height / 2.0));
	dimensions.real_top = round(((double)screen.height / 2.0) - (dimensions.real_height / 2.0));
	dimensions.bottom = dimensions.top + dimensions.height;

	return (dimensions);
}

// static t_collider get_collider_type(t_map worldmap, t_position pos)
// {
// 	t_grid_position grid_pos = to_grid_position(worldmap, pos);
// 	if(grid_pos.x == INVALID || grid_pos.y == INVALID)
// 		return (INVALID);
// 	return (worldmap.matrix[grid_pos.y][grid_pos.x]);
// }

void draw_slice(t_data *data, int slice_col, t_ray *ray)
{
	t_dimensions dimensions = get_dimensions(ray->distance, data->player, data->screen);
	draw_ceiling_slice(data, slice_col, dimensions.top, dimensions.height);
	draw_floor_slice(data, slice_col, dimensions.bottom, dimensions.height);

	if (is_facing_north(ray->angle) && ray->orientation == HORIZONTAL)
		draw_wall_slice(data, slice_col, dimensions, ray, SO);
	else if (is_facing_south(ray->angle) && ray->orientation == HORIZONTAL)
		draw_wall_slice(data, slice_col, dimensions, ray, NO);
	else if (is_facing_west(ray->angle) && ray->orientation == VERTICAL)
		draw_wall_slice(data, slice_col, dimensions, ray, EA);
	else if (is_facing_east(ray->angle) && ray->orientation == VERTICAL)
		draw_wall_slice(data, slice_col, dimensions, ray, WE);
}
