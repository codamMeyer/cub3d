#include "sprite_render.h"
#include "sprite.h"
#include <assert.h>
#include <math.h>
#include <raycast/raycast_utils.h>
#include <render/render_utils.h>
#include "sprite_render_utils.h"
#include <stdio.h>
#include <utils/angle_utils.h>
#include <utils/math_utils.h>
#include <utils/grid_position.h>
#include <raycast/horizontal_detection.h>
#include <raycast/vertical_detection.h>

void	draw_sprites_slice(t_data *data,
							int col,
							double dist_to_wall,
							t_sprite sprite)
{
	t_texture_position	pos;
	t_color				color;
	int					y;

	if (is_visible(sprite, col, dist_to_wall))
	{
		y = max_i(sprite.start.y, 0);
		while (y <= min_i(sprite.end.y, data->screen.height))
		{
			pos = get_texture_position(&data->textures[SP], \
									   sprite.dimensions, y, \
									   col - sprite.start.x);
			color = get_pixel_color(&data->textures[SP], pos.x, pos.y);
			color = apply_shading(sprite.dist_from_player, color, 400);
			if (!is_black(color))
				my_mlx_pixel_put(&data->img, col, y, color);
			y++;
		}
	}
}

void	get_sprite_projection(t_player player,
											t_window screen,
											t_sprite *sprite)
{
	const double		sprite_angle = get_sprite_angle(player.position, sprite->center);
	const double		sprite_to_player_angle = \
							abs_value(sprite_angle - player.angle);
	const double		sprite_screen_center = \
							get_sprite_screen_center(player.dist_to_plane, \
													sprite_to_player_angle, \
													player.angle, \
													sprite_angle);
	const double		sprite_screen_x = (double)screen.width / 2.0 \
											- sprite_screen_center;

	sprite->dist_from_player = fix_fisheye_effect(sprite->dist_from_player, \
												sprite_to_player_angle);
	sprite->dimensions = get_dimensions(sprite->dist_from_player, player, screen);
	sprite->start.y = ((double)screen.height / 2.0) - \
					((double)sprite->dimensions.height / 2.0);
	sprite->end.y = sprite->start.y + screen.height;
	sprite->start.x = sprite_screen_x - ((double)sprite->dimensions.width / 2.0);
	sprite->end.x = sprite->start.x + sprite->dimensions.width;
}

void	draw_sprites(t_data *data,
							int col,
							t_ray *ray,
							double wall_dist)
{
	int					i;
	(void)ray;
	i = 0;
	while (i < data->visible_sprites)
	{
		if (col >= data->sprites[i].start.x && col <= data->sprites[i].end.x)
			draw_sprites_slice(data, col, wall_dist, data->sprites[i]);
		++i;
	}
}

t_bool in_sprites_list(t_sprite *sprites, t_position center, int index)
{
	int i;

	i = 0;
	while (i < index)
	{
		if (is_same_pos(sprites[i].center, center))
			return(TRUE);
		++i;
	}
	return (FALSE);
}

static void	swap(t_sprite *cur, t_sprite *prev)
{
	const t_sprite	tmp = *cur;

	*cur = *prev;
	*prev = tmp;
}

void	sort(t_sprite *sprites, int sprite_count)
{
	t_bool	swapped;
	int		i;

	if (sprite_count <= 1)
		return ;
	swapped = TRUE;
	while (swapped)
	{
		swapped = FALSE;
		i = 1;
		while (i < sprite_count)
		{
			if (sprites[i].dist_from_player > sprites[i - 1].dist_from_player)
			{
				swapped = TRUE;
				swap(&sprites[i], &sprites[i - 1]);
			}
			++i;
		}
	}
}

static t_intersections create_intersections(t_player player, double angle)
{
	const double			tan_angle = tan(degree_to_radians(angle));
	const t_intersections	intersections = {
	.hor_increment = get_horizontal_detection_increment(angle, tan_angle),
	.ver_increment = get_vertical_detection_increment(angle, tan_angle),
	.horizontal = get_first_horizontal_intersection(player, angle, tan_angle),
	.vertical = get_first_vertical_intersection(player, angle, tan_angle),
	};

	return (intersections);
}

void find_sprites(t_data *data, int *index, double angle)
{
	t_intersections	intersections;
	t_position pos;

	intersections = create_intersections(data->player, angle);
	while (is_valid_position(data->worldMap, intersections.horizontal) || \
		   is_valid_position(data->worldMap, intersections.vertical))
	{
		if (detect_hit(data->worldMap, intersections.horizontal, SPRITE))
		{
			pos = compute_grid_center(data->worldMap, intersections.horizontal);
			if (!in_sprites_list(data->sprites, pos, *index))
			{
				data->sprites[*index].center = pos;
				data->sprites[*index].dist_from_player = get_distance_from_player(data->sprites[*index].center, data->player.position);
				get_sprite_projection(data->player, data->screen, &data->sprites[*index]);
				++(*index);
			}
		}
		if (detect_hit(data->worldMap, intersections.vertical, SPRITE))
		{
			pos = compute_grid_center(data->worldMap, intersections.vertical);
			if (!in_sprites_list(data->sprites, pos, *index))
			{
				data->sprites[*index].center = pos;
				data->sprites[*index].dist_from_player = get_distance_from_player(data->sprites[*index].center, data->player.position);
				get_sprite_projection(data->player, data->screen, &data->sprites[*index]);
				++(*index);
			}
		}
		apply_incremento_to_intersections(&intersections);
	}
}

int	get_all_sprites(t_data *data)
{
	const double	ray_increment = (double)data->player.FOV / (double)data->screen.width;
	int				sprites_count;
	int				col;
	t_ray			ray;

	ray.angle = data->player.angle + (data->player.FOV / 2);
	col = 0;
	sprites_count = 0;
	while (col < data->screen.width)
	{
		ray.angle = fix_angle(ray.angle);
		find_sprites(data, &sprites_count, ray.angle);
		ray.angle -= ray_increment;
		++col;
	}
	sort(data->sprites, sprites_count);
	return (sprites_count);
}
