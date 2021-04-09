#include "render.h"
#include "color.h"
#include "render_utils.h"
#include <utils/direction.h>

static void draw_ceiling_slice(t_data *data, int slice_col, int wall_top, int wall_height)
{
	int i = 0;
	while (i < wall_top + (wall_height / 2))
	{
		my_mlx_pixel_put(&data->img, slice_col, i, data->ceiling);
		++i;
	}
}

static void draw_wall_slice(t_data *data,
							int slice_col,
							t_dimensions wall_dimensions,
							t_ray *ray,
							t_texture_enum texture)
{
	int wall_index = wall_dimensions.top;
	t_color_rgba color;

	t_texture_position texture_pos;
	while (wall_index <= wall_dimensions.bottom)
	{
		texture_pos =
			get_wall_texture_position(&data->textures[texture], ray, wall_dimensions, wall_index);
		color = get_pixel_color(&data->textures[texture], texture_pos.x, texture_pos.y);
		if (ray->orientation == VERTICAL)
		{
			color.red *= 0.8;
			color.green *= 0.8;
			color.blue *= 0.8;
		}
		color = apply_shading(ray->distance, color, 400);
		if (!is_black(color))
			my_mlx_pixel_put(&data->img, slice_col, wall_index, color);
		++wall_index;
	}
}

static void draw_floor_slice(t_data *data, int slice_col, int wall_bottom, int wall_height)
{
	int i = wall_bottom - (wall_height / 2);
	while (i < data->screen.height)
	{
		t_color_rgba color =
			apply_floor_shading(i,
								data->floor,
								(data->screen.height / 2) + (data->screen.height / 10));
		my_mlx_pixel_put(&data->img, slice_col, i, color);
		++i;
	}
}

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
