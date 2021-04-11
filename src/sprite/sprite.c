#include "sprite.h"
#include <math.h>
#include <raycast/horizontal_detection.h>
#include <raycast/raycast_utils.h>
#include <raycast/vertical_detection.h>
#include <render/render_utils.h>
#include <stdio.h>
#include <utils/angle_utils.h>
#include <utils/direction.h>
#include <utils/math_utils.h>

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

void add_sprites_to_list(t_map worldMap, t_list **sprites, t_position increment, t_position ray)
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
		ray.x += increment.x;
		ray.y += increment.y;
	}
}

void find_sprite_list_horizontal_line(t_player player,
									  t_map worldMap,
									  t_list **sprites,
									  double ray_angle)
{
	const double tan_angle = tan(degree_to_radians(ray_angle));
	const t_position increment = get_increment_for_horizontal_detection(ray_angle, tan_angle);
	t_position pos;

	pos = get_first_horizontal_intersection(player, ray_angle, tan_angle);
	add_sprites_to_list(worldMap, sprites, increment, pos);
}

void find_sprite_list_vertical_line(t_player player,
									t_map worldMap,
									t_list **sprites,
									double ray_angle)
{
	const double tan_angle = tan(degree_to_radians(ray_angle));
	const t_position increment = get_increment_for_vertical_detection(ray_angle, tan_angle);
	t_position pos;

	pos = get_first_vertical_intersection(player, ray_angle, tan_angle);
	add_sprites_to_list(worldMap, sprites, increment, pos);
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
	return (sprite.dist_from_player < dist_to_wall && sprite.dist_from_player > 0.0 &&
			col >= sprite.start.x && col <= sprite.end.x);
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

void compute_sprite_dist_from_player(t_player player, t_list *sprites)
{
	t_list *cur;
	t_sprite *sprite;

	cur = sprites;
	while (cur != NULL)
	{
		sprite = (t_sprite *)cur->content;
		sprite->dist_from_player = get_distance_from_player(sprite->center, player.position);
		cur = cur->next;
	}
}

t_bool swap(t_list *cur, t_list *prev)
{
	const t_sprite *cur_sprite = (t_sprite *)cur->content;
	const t_sprite *prev_sprite = (t_sprite *)prev->content;

	void *tmp;
	if (cur_sprite->dist_from_player > prev_sprite->dist_from_player)
	{
		tmp = cur->content;
		cur->content = prev->content;
		prev->content = tmp;
		return (TRUE);
	}
	return (FALSE);
}

void sort_sprites(t_list *sprites)
{
	const int size = ft_lstsize(sprites);
	t_list *prev;
	t_list *cur;
	t_bool swapped;
	int i;

	if (size <= 1)
		return;
	swapped = TRUE;
	while (swapped)
	{
		swapped = FALSE;
		prev = sprites;
		cur = sprites->next;
		i = 1;
		while (i < size)
		{
			swapped = swap(cur, prev);
			cur = cur->next;
			++i;
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

void find_and_draw_sprites(int col, t_data *data, t_ray *ray, double wall_dist)
{
	t_list *sprites;
	t_list *cur;
	t_sprite_projection projection;

	sprites = NULL;
	find_sprites(data->player, data->worldMap, &sprites, ray->angle);
	compute_sprite_dist_from_player(data->player, sprites);
	sort_sprites(sprites);
	cur = sprites;
	while (cur != NULL)
	{
		projection =
			create_sprite_projection(data->player, data->screen, *(t_sprite *)(cur->content));
		draw_sprites_slice(data, col, wall_dist, projection);
		cur = cur->next;
	}
	ft_lstclear(&sprites, free);
}