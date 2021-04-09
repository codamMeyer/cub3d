#include "sprite.h"
#include <math.h>
#include <raycast/horizontal_detection.h>
#include <raycast/raycast_utils.h>
#include <raycast/raycast_utils2.h>
#include <raycast/vertical_detection.h>
#include <render/render_utils.h>
#include <stdio.h>
#include <utils/direction.h>
#include <utils/math_utils.h>
#include <utils/utils.h>
#include <utils/math_utils2.h>

static t_bool hit_sprite(t_map worldMap, t_position pos)
{
	t_grid_position grid_pos = to_grid_position(worldMap, pos);
	if (!is_valid_grid_position(worldMap, grid_pos))
		return (INVALID);
	keep_inside_map(&grid_pos, worldMap);
	if (worldMap.matrix[grid_pos.y][grid_pos.x] == SPRITE)
		return (TRUE);
	return (FALSE);
}

void add_sprites_to_list(t_map worldMap,
						 t_list **sprites,
						 double x_increment,
						 double y_increment,
						 t_position ray)
{
	t_sprite *sprite;
	t_bool hit = FALSE;
	t_grid_position grid_pos;

	while (TRUE)
	{
		hit = hit_sprite(worldMap, ray);
		if (hit == INVALID)
			break;
		if (hit)
		{
			sprite = malloc(sizeof(t_sprite));
			grid_pos = to_grid_position(worldMap, ray);
			sprite->center = get_grid_center(grid_pos);
			t_list *new_element = ft_lstnew(sprite);
			ft_lstadd_front(sprites, new_element);
		}
		ray.x += x_increment;
		ray.y += y_increment;
	}
}

void find_sprite_list_horizontal_line(t_player player,
									  t_map worldMap,
									  t_list **sprites,
									  double ray_angle)
{
	t_position pos;
	double tan_angle = tan(degree_to_radians(ray_angle));
	double y_increment = get_y_increment_for_horizontal_detection(ray_angle);
	double x_increment = get_x_increment_for_horizontal_detection(ray_angle, tan_angle);
	pos = get_first_horizontal_intersection(player, ray_angle, tan_angle);
	add_sprites_to_list(worldMap, sprites, x_increment, y_increment, pos);
}

void find_sprite_list_vertical_line(t_player player,
									t_map worldMap,
									t_list **sprites,
									double ray_angle)
{
	t_position pos;
	double tan_angle = tan(degree_to_radians(ray_angle));
	double x_increment = get_x_increment_for_vertical_detection(ray_angle);
	double y_increment = get_y_increment_for_vertical_detection(ray_angle, tan_angle);
	pos = get_first_vertical_intersection(player, ray_angle, tan_angle);
	add_sprites_to_list(worldMap, sprites, x_increment, y_increment, pos);
}

static double radians_to_degrees(double radians)
{
	return (180.0 * radians / M_PI);
}

void get_sprite_values(t_player player, t_window screen, t_sprite *sprite)
{
	const t_position delta = {.x = sprite->center.x - player.position.x,
							  .y = sprite->center.y - player.position.y};
	const double sprite_angle =
		fix_angle(radians_to_degrees(atan2(-delta.y, delta.x))); //cartesian plan is inverted
	const double sprite_to_player_angle = abs_value(sprite_angle - player.angle);
	sprite->dist_to_sprite = get_distance_from_player(sprite->center, player.position);

	double sprite_screen_center =
		player.dist_to_plane * tan(degree_to_radians(sprite_to_player_angle));
	if (player.angle > sprite_angle)
		sprite_screen_center *= -1;
	double sprite_screen_x = (double)screen.width / 2.0 - sprite_screen_center;
	sprite->dist_to_sprite = fix_fisheye_effect(sprite->dist_to_sprite, sprite_to_player_angle);
	sprite->dimensions = get_dimensions(sprite->dist_to_sprite, player, screen);
	double projected_sprite_width;
	sprite->height = sprite->dimensions.height;
	sprite->start_y = (screen.height / 2.0) - (sprite->height / 2.0);
	sprite->end_y = sprite->start_y + screen.height;
	projected_sprite_width = sprite->dimensions.width;
	sprite->start_x = sprite_screen_x - (projected_sprite_width / 2.0);
	sprite->end_x = sprite->start_x + projected_sprite_width;
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

t_bool is_visible(t_sprite sprite, int col, double dist_to_wall)
{
	return (sprite.dist_to_sprite < dist_to_wall && sprite.dist_to_sprite > 0.0 &&
			col >= sprite.start_x && col <= sprite.end_x);
}

void draw_sprites_slice(t_data *data, int col, double dist_to_wall, t_sprite sprite)
{
	t_texture_position pos;
	t_color_rgba color;
	int y;

	if (is_visible(sprite, col, dist_to_wall))
	{
		y = max_i(sprite.start_y, 0);
		while (y <= min_i(sprite.end_y, data->screen.height))
		{
			pos = get_texture_position(&data->textures[SP],
									   sprite.dimensions,
									   y,
									   col - sprite.start_x);
			color = get_pixel_color(&data->textures[SP], pos.x, pos.y);
			color = apply_shading(sprite.dist_to_sprite, color, 400);
			if (!is_black(color))
				my_mlx_pixel_put(&data->img, col, y, color);
			y++;
		}
	}
}

void find_sprites(t_player player, t_map worldMap, t_list **sprites, double ray_angle)
{

	if (!is_left_or_right(ray_angle))
		find_sprite_list_horizontal_line(player, worldMap, sprites, ray_angle);
	if (!is_up_or_down(ray_angle))
		find_sprite_list_vertical_line(player, worldMap, sprites, ray_angle);
}
