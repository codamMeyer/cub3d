#include <game/ray_casting_logic.h>
#include <game/render.h>
#include <game/sprite.h>
#include <game/wall_detection.h>
#include <math.h>
#include <stdio.h>
#include <utils/direction.h>
#include <utils/math_utils.h>
#include <utils/utils.h>

static t_bool hit_sprite(t_map worldMap, t_position pos)
{
	t_grid_position grid_pos = to_grid_position(worldMap, pos);
	if (!is_valid_grid_position(worldMap, grid_pos))
		return (INVALID);
	grid_pos.x = max_i(grid_pos.x, 0);
	grid_pos.y = max_i(grid_pos.y, 0);
	grid_pos.x = min_i(grid_pos.x, worldMap.width - 1);
	grid_pos.y = min_i(grid_pos.y, worldMap.height - 1);

	if (worldMap.matrix[grid_pos.y][grid_pos.x] == SPRITE)
	{
		return (TRUE);
	}
	return (FALSE);
}

static t_sprite find_sprite(t_map worldMap, double x_increment, double y_increment, t_position ray)
{
	t_sprite sprite;
	while (!hit_sprite(worldMap, ray))
	{
		ray.x += x_increment;
		ray.y += y_increment;
	}
	sprite.grid_pos = to_grid_position(worldMap, ray);
	sprite.center = get_grid_center(sprite.grid_pos);
	return (sprite);
}

t_sprite find_sprite_horizontal_line(t_data *data, double ray_angle)
{
	t_position pos;
	t_sprite sprite;
	if (is_straight_left_or_right(&pos, ray_angle))
	{
		sprite.grid_pos.x = -1;
		sprite.grid_pos.y = -1;
		return (sprite);
	}
	double tan_angle = tan(degree_to_radians(ray_angle));
	double y_increment = get_y_increment_for_horizontal_detection(ray_angle);
	double x_increment = get_x_increment_for_horizontal_detection(ray_angle, tan_angle);
	pos = get_first_horizontal_intersection(data->player, ray_angle, tan_angle);
	return (find_sprite(data->worldMap, x_increment, y_increment, pos));
}

t_sprite find_sprite_vertical_line(t_data *data, double ray_angle)
{
	t_position pos;
	t_sprite sprite;
	if (is_straight_up_or_down(&pos, ray_angle))
	{
		sprite.center = pos;
		sprite.grid_pos.x = -1;
		sprite.grid_pos.y = -1;
		return (sprite);
	}
	double tan_angle = tan(degree_to_radians(ray_angle));
	double x_increment = get_x_increment_for_vertical_detection(ray_angle);
	double y_increment = get_y_increment_for_vertical_detection(ray_angle, tan_angle);
	pos = get_first_vertical_intersection(data->player, ray_angle, tan_angle);
	return (find_sprite(data->worldMap, x_increment, y_increment, pos));
}

double get_sprite_distance(t_position sprite_center, t_position player_coord)
{
	const double x_diff = (player_coord.x - sprite_center.x) * (player_coord.x - sprite_center.x);
	const double y_diff = (player_coord.y - sprite_center.y) * (player_coord.y - sprite_center.y);
	return (sqrt(x_diff + y_diff));
}

t_sprite
find_closest_sprite(t_map worldmap, t_sprite horizontal, t_sprite vertical, t_player player)
{
	if (is_valid_grid_position(worldmap, horizontal.grid_pos))
	{
		const double h_dist = get_sprite_distance(horizontal.center, player.position);
		if (is_valid_grid_position(worldmap, vertical.grid_pos))
		{
			const double v_dist = get_sprite_distance(vertical.center, player.position);
			if (h_dist < v_dist)
				return (horizontal);
			return (vertical);
		}
		return (horizontal);
	}
	else
		return (vertical);
}

static double radians_to_degrees(double radians)
{
	return (180.0 * radians / PI);
}

void get_sprite_values(t_data *data, t_sprite *sprite)
{
	const t_position delta = {.x = sprite->center.x - data->player.position.x,
							  .y = sprite->center.y - data->player.position.y};
	//minus is necessary because the cartesian plan is inverted
	const double sprite_angle = fix_angle(radians_to_degrees(atan2(-delta.y, delta.x)));

	sprite->dist_to_sprite = get_sprite_distance(sprite->center, data->player.position);
	const double sprite_to_player_angle = abs_value(sprite_angle - data->player.angle);

	// if (sprite->center.x > data->player.position.x)
	// 	sprite_to_player_angle = sprite_angle - data->player.angle;
	// else
	// 	sprite_to_player_angle = data->player.angle - sprite_angle;

	const double dist_to_plane =
		((double)data->screen.width / 2.0) / tan(degree_to_radians((double)data->player.FOV / 2.0));

	double sprite_dist_screen = dist_to_plane * tan(degree_to_radians(sprite_to_player_angle));
	// if (sprite->center.x < data->player.position.x || is_facing_north(data->player.angle))
	// 	sprite_dist_screen = -sprite_dist_screen;
	if (data->player.angle > sprite_angle)
		sprite_dist_screen *= -1;
	double sprite_screen_x = (double)data->screen.width / 2.0 - sprite_dist_screen;

	double corrected_dist = cos(degree_to_radians(sprite_to_player_angle)) * sprite->dist_to_sprite;
	sprite->dist_to_sprite = corrected_dist;

	sprite->dimensions = get_dimensions(sprite->dist_to_sprite, data->player, data->screen);
	double projected_sprite_width;
	sprite->height = sprite->dimensions.height;
	sprite->start_y = (data->screen.height / 2.0) - (sprite->height / 2.0);
	sprite->end_y = sprite->start_y + data->screen.height;
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

t_color sample_sprites_vertical_line(t_data *data, int x, int y, t_sprite sprite)
{
	t_texture_position pos = get_texture_position(&data->textures[SP], sprite.dimensions, y, x);
	t_color color;

	color = get_pixel_color(&data->textures[SP], pos.x, pos.y);
	return (color);
}

void draw_sprites_vertical_line(t_data *data, int col, double dist_to_wall, t_sprite sprite)
{
	int y;

	if (sprite.dist_to_sprite < dist_to_wall && sprite.dist_to_sprite > 0.0 &&
		col >= sprite.start_x && col <= sprite.end_x)
	{
		y = max_i(sprite.start_y, 0);
		while (y <= min_i(sprite.end_y, data->screen.height))
		{
			t_color color = sample_sprites_vertical_line(data, col - sprite.start_x, y, sprite);
			if (color != 0xFF000000)
				my_mlx_pixel_put(&data->img, col, y, color);
			y++;
		}
	}
}

t_sprite find_sprites(t_data *data, double ray_angle)
{
	t_sprite hor;
	t_sprite ver;

	hor = find_sprite_horizontal_line(data, ray_angle);
	ver = find_sprite_vertical_line(data, ray_angle);
	return (find_closest_sprite(data->worldMap, hor, ver, data->player));
}
