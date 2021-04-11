#include "sprite_render.h"
#include "sprite.h"
#include <assert.h>
#include <math.h>
#include <raycast/raycast_utils.h>
#include <render/render_utils.h>
#include <stdio.h>
#include <utils/angle_utils.h>
#include <utils/math_utils.h>

void compute_sprite_dist_from_player(t_player player, t_sprite *sprites, int num_sprites)
{
	int i = 0;
	while (i < num_sprites)
	{
		sprites[i].dist_from_player = get_distance_from_player(sprites[i].center, player.position);
		++i;
	}
}

double get_sprite_screen_center(double dist_to_plane,
								double sprite_to_player_angle,
								double player_angle,
								double sprite_angle)
{
	double sprite_screen_center;

	sprite_screen_center = dist_to_plane * tan(degree_to_radians(sprite_to_player_angle));
	if (player_angle > sprite_angle)
		sprite_screen_center *= -1;
	return (sprite_screen_center);
}

double get_sprite_angle(t_player player, t_sprite sprite)
{
	const t_position delta = {.x = sprite.center.x - player.position.x,
							  .y = sprite.center.y - player.position.y};
	const double sprite_angle =
		fix_angle(radians_to_degrees(atan2(-delta.y, delta.x))); //cartesian plan is inverted

	return (sprite_angle);
}

static t_texture_position
get_texture_position(const t_texture *texture, t_dimensions dimensions, int y_index, double x)
{
	const double texture_to_sprite_ratio = (double)texture->height / (double)dimensions.real_height;

	const int wall_pixel_position = (y_index - dimensions.real_top);
	t_texture_position pos;

	pos.y = floor(wall_pixel_position * texture_to_sprite_ratio);
	pos.x = (int)x * texture_to_sprite_ratio;
	return (pos);
}

t_bool is_visible(t_sprite_projection sprite, int col, double dist_to_wall)
{
	return (sprite.dist_from_player < dist_to_wall && col >= sprite.start.x && col <= sprite.end.x);
}

t_sprite_projection create_sprite_projection(t_player player, t_window screen, t_sprite sprite)
{
	const double sprite_angle = get_sprite_angle(player, sprite);
	const double sprite_to_player_angle = abs_value(sprite_angle - player.angle);
	const double sprite_screen_center = get_sprite_screen_center(player.dist_to_plane,
																 sprite_to_player_angle,
																 player.angle,
																 sprite_angle);
	const double sprite_screen_x = (double)screen.width / 2.0 - sprite_screen_center;
	t_sprite_projection projection;

	projection.dist_from_player =
		fix_fisheye_effect(sprite.dist_from_player, sprite_to_player_angle);
	projection.dimensions = get_dimensions(projection.dist_from_player, player, screen);
	projection.start.y = (screen.height / 2.0) - (projection.dimensions.height / 2.0);
	projection.end.y = projection.start.y + screen.height;
	projection.start.x = sprite_screen_x - (projection.dimensions.width / 2.0);
	projection.end.x = projection.start.x + projection.dimensions.width;

	return (projection);
}

void draw_sprites_slice(t_data *data, int col, double dist_to_wall, t_sprite_projection sprite)
{
	t_texture_position pos;
	t_color_rgba color;
	int y;

	if (is_visible(sprite, col, dist_to_wall))
	{
		y = max_i(sprite.start.y, 0);
		while (y <= min_i(sprite.end.y, data->screen.height))
		{
			pos = get_texture_position(&data->textures[SP],
									   sprite.dimensions,
									   y,
									   col - sprite.start.x);
			color = get_pixel_color(&data->textures[SP], pos.x, pos.y);
			color = apply_shading(sprite.dist_from_player, color, 400);
			if (!is_black(color))
				my_mlx_pixel_put(&data->img, col, y, color);
			y++;
		}
	}
}

void find_and_draw_sprites(int col, t_data *data, t_ray *ray, double wall_dist)
{
	t_sprite_projection projection;
	const int sprite_count = find_sprites(data->player, data->worldMap, data->sprites, ray->angle);
	compute_sprite_dist_from_player(data->player, data->sprites, sprite_count);
	sort_sprites(data->sprites, sprite_count);
	int i = 0;
	while (i < sprite_count)
	{
		projection = create_sprite_projection(data->player, data->screen, data->sprites[i]);
		draw_sprites_slice(data, col, wall_dist, projection);
		++i;
	}
}
