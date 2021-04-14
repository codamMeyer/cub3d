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

void	draw_sprites_slice(t_data *data,
							int col,
							double dist_to_wall,
							t_sprite_projection sprite)
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

t_sprite_projection	create_sprite_projection(t_player player,
											t_window screen,
											t_sprite sprite)
{
	const double		sprite_angle = get_sprite_angle(player, sprite);
	const double		sprite_to_player_angle = \
							abs_value(sprite_angle - player.angle);
	const double		sprite_screen_center = \
							get_sprite_screen_center(player.dist_to_plane, \
													sprite_to_player_angle, \
													player.angle, \
													sprite_angle);
	const double		sprite_screen_x = (double)screen.width / 2.0 \
											- sprite_screen_center;
	t_sprite_projection	proj;

	proj.dist_from_player = fix_fisheye_effect(sprite.dist_from_player, \
												sprite_to_player_angle);
	proj.dimensions = get_dimensions(proj.dist_from_player, player, screen);
	proj.start.y = ((double)screen.height / 2.0) - \
					((double)proj.dimensions.height / 2.0);
	proj.end.y = proj.start.y + screen.height;
	proj.start.x = sprite_screen_x - ((double)proj.dimensions.width / 2.0);
	proj.end.x = proj.start.x + proj.dimensions.width;
	return (proj);
}

void	compute_sprite_dist_from_player(t_player player,
										t_sprite *sprites,
										int num_sprites)
{
	int	i;

	i = 0;
	while (i < num_sprites)
	{
		sprites[i].dist_from_player = \
				get_distance_from_player(sprites[i].center, player.position);
		++i;
	}
}

void	find_and_draw_sprites(int col,
							t_data *data,
							t_ray *ray,
							double wall_dist)
{
	const int			sprite_count = find_sprites(data->player, \
													data->worldMap, \
													data->sprites, \
													ray->angle);
	t_sprite_projection	projection;
	int					i;

	compute_sprite_dist_from_player(data->player, data->sprites, sprite_count);
	sort_sprites(data->sprites, sprite_count);
	i = 0;
	while (i < sprite_count)
	{
		projection = create_sprite_projection(data->player, \
												data->screen, \
												data->sprites[i]);
		draw_sprites_slice(data, col, wall_dist, projection);
		++i;
	}
}
