#include "render.h"
#include "color.h"
#include "render_utils.h"
#include <utils/direction.h>
#include "shade.h"

static void	draw_ceiling_slice(t_data *data,
								int slice_col,
								int wall_top,
								int wall_height)
{
	const double	shading_dist = \
						(data->screen.height / 2) + (data->screen.height / 20);
	int				i;
	t_color			color;

	i = 0;
	while (i < wall_top + (wall_height / 2))
	{
		color = apply_ceiling_shading(i, data->ceiling, shading_dist);
		my_mlx_pixel_put(&data->img, slice_col, i, color);
		++i;
	}
}

static void	draw_floor_slice(t_data *data,
								int slice_col,
								int wall_bottom,
								int wall_height)
{
	const double	shading_dist = \
						(data->screen.height / 2) + (data->screen.height / 20);
	int				i;
	t_color			color;

	i = wall_bottom - (wall_height / 2);
	while (i < data->screen.height)
	{
		color = apply_floor_shading(i, data->floor, shading_dist);
		my_mlx_pixel_put(&data->img, slice_col, i, color);
		++i;
	}
}

static void	draw_wall_slice(t_data *data,
							int slice_col,
							t_ray *ray,
							t_texture_enum texture)
{
	const t_dimensions	wall_dimensions = \
					get_dimensions(ray->distance, data->player, data->screen);
	int					wall_index;
	t_color				color;
	t_texture_position	texture_pos;

	wall_index = wall_dimensions.top;
	while (wall_index <= wall_dimensions.bottom)
	{
		texture_pos = get_wall_texture_position(&data->textures[texture], \
											ray, wall_dimensions, wall_index);
		color = get_pixel_color(&data->textures[texture], \
								texture_pos.x, texture_pos.y);
		if (ray->orientation == VERTICAL)
			color = get_darker_color(color, 0.8);
		color = apply_shading(ray->distance, color, 400);
		my_mlx_pixel_put(&data->img, slice_col, wall_index, color);
		++wall_index;
	}
}

void	draw_slice(t_data *data, int slice_col, t_ray *ray)
{
	const t_dimensions	dimensions = \
					get_dimensions(ray->distance, data->player, data->screen);

	draw_ceiling_slice(data, slice_col, dimensions.top, dimensions.height);
	draw_floor_slice(data, slice_col, dimensions.bottom, dimensions.height);
	if (is_facing_north(ray->angle) && ray->orientation == HORIZONTAL)
		draw_wall_slice(data, slice_col, ray, SO);
	else if (is_facing_south(ray->angle) && ray->orientation == HORIZONTAL)
		draw_wall_slice(data, slice_col, ray, NO);
	else if (is_facing_west(ray->angle) && ray->orientation == VERTICAL)
		draw_wall_slice(data, slice_col, ray, EA);
	else if (is_facing_east(ray->angle) && ray->orientation == VERTICAL)
		draw_wall_slice(data, slice_col, ray, WE);
}
