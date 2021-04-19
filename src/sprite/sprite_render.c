#include "sprite_render_utils.h"
#include "sprite_render.h"
#include "sprite_projection.h"
#include <render/render_utils.h>
#include <utils/angle_utils.h>
#include <utils/math_utils.h>
#include <utils/grid_position.h>
#include <render/shade.h>

static void	add_sprites_to_list(t_data *data, t_position position)
{
	const t_position	pos = compute_grid_center(data->worldMap, position);
	const int			i = data->visible_sprites;

	if (!in_sprites_list(data->sprites, pos, data->visible_sprites))
	{
		data->sprites[i].center = pos;
		data->sprites[i].dist_from_player = \
		get_distance_from_player(pos, data->player.position);
		get_sprite_projection(data->player, data->screen, &data->sprites[i]);
		++(data->visible_sprites);
	}
}

static void	find_sprites(t_data *data, double angle)
{
	t_intersections	intersections;

	intersections = create_intersections(&data->player, angle);
	while (is_valid_position(data->worldMap, intersections.horizontal) || \
		   is_valid_position(data->worldMap, intersections.vertical))
	{
		if (detect_hit(data->worldMap, intersections.horizontal, SPRITE))
			add_sprites_to_list(data, intersections.horizontal);
		if (detect_hit(data->worldMap, intersections.vertical, SPRITE))
			add_sprites_to_list(data, intersections.vertical);
		apply_incremento_to_intersections(&intersections);
	}
}

static void	draw_sprites_slice(t_data *data,
							int col,
							double dist_to_wall,
							const t_sprite *sprite)
{
	t_texture_position	pos;
	t_color				color;
	int					y;

	if (is_visible(sprite->dist_from_player, dist_to_wall))
	{
		y = max_i(sprite->start.y, 0);
		while (y <= min_i(sprite->end.y, data->screen.height))
		{
			pos = get_texture_position(&data->textures[SP], \
									   &sprite->dimensions, y, \
									   col - sprite->start.x);
			color = get_pixel_color(&data->textures[SP], pos.x, pos.y);
			color = apply_shading(sprite->dist_from_player, color, 400);
			my_mlx_pixel_put(&data->img, col, y, color);
			y++;
		}
	}
}

void	draw_sprites(t_data *data, int col, double wall_dist)
{
	int	i;

	i = 0;
	while (i < data->visible_sprites)
	{
		if (col >= data->sprites[i].start.x && col <= data->sprites[i].end.x)
			draw_sprites_slice(data, col, wall_dist, &data->sprites[i]);
		++i;
	}
}

void	get_all_sprites(t_data *data)
{
	const double	ray_increment = (double)data->player.FOV \
									/ (double)data->screen.width;
	int				col;
	t_ray			ray;

	data->visible_sprites = 0;
	ray.angle = data->player.angle + (data->player.FOV / 2);
	col = 0;
	while (col < data->screen.width)
	{
		ray.angle = fix_angle(ray.angle);
		find_sprites(data, ray.angle);
		ray.angle -= ray_increment;
		++col;
	}
	sort(data->sprites, data->visible_sprites);
}
