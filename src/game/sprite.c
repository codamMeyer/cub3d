#include <game/ray_casting_logic.h>
#include <game/render.h>
#include <game/sprite.h>
#include <math.h>
#include <stdio.h>
#include <utils/math_utils.h>
#include <utils/utils.h>

static t_bool hit_sprite(t_map worldMap, t_position pos)
{
	t_grid_position grid_pos = to_grid_position(worldMap, pos);
	if(!is_valid_grid_position(worldMap, grid_pos))
		return (INVALID);
	grid_pos.x = max_i(grid_pos.x, 0);
	grid_pos.y = max_i(grid_pos.y, 0);
	grid_pos.x = min_i(grid_pos.x, worldMap.width - 1);
	grid_pos.y = min_i(grid_pos.y, worldMap.height - 1);

	if(worldMap.matrix[grid_pos.y][grid_pos.x] == SPRITE)
	{
		return (TRUE);
	}
	return (FALSE);
}

static t_sprite find_sprite(t_map worldMap, double x_increment, double y_increment, t_position ray)
{
	t_sprite sprite;
	while(!hit_sprite(worldMap, ray))
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
	if(is_straight_left_or_right(&pos, ray_angle))
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
	if(is_straight_up_or_down(&pos, ray_angle))
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
	if(is_valid_grid_position(worldmap, horizontal.grid_pos))
	{
		const double h_dist = get_sprite_distance(horizontal.center, player.position);
		if(is_valid_grid_position(worldmap, vertical.grid_pos))
		{
			const double v_dist = get_sprite_distance(vertical.center, player.position);
			if(h_dist < v_dist)
				return (horizontal);
			return (vertical);
		}
		return (horizontal);
	}
	else
		return (vertical);
}

static t_position get_sprite_transform_value(t_player *player, t_position pos, t_window screen)
{

	double dir_x = cos(degree_to_radians(player->angle));
	double dir_y = sin(degree_to_radians(player->angle));
	t_position sprite_pos;

	sprite_pos.x = pos.x - player->position.x;
	sprite_pos.y = pos.y - player->position.y;

	double inv_det = 1.0 / (screen.width * dir_y - dir_x * screen.height);

	t_position transform;
	transform.x = inv_det * ((dir_y * sprite_pos.x) - (dir_x * sprite_pos.y));

	transform.y = inv_det * (-screen.height * sprite_pos.x + screen.width * sprite_pos.y);

	return (transform);
}

static void draw_sprite(t_data *data, t_sprite sprite)
{
	t_color color;
	t_dimentions sprite_dimentions;
	t_texture_position texture_pos;

	t_position transform = get_sprite_transform_value(&data->player, sprite.center, data->screen);

	int sprite_screen_x = ((double)data->screen.width / 2.0) * (1.0 + transform.x / transform.y);

	sprite_dimentions.height = abs_value(floor((double)data->screen.height / transform.y));
	sprite_dimentions.top =
		(double)data->screen.height / 2.0 - (double)sprite_dimentions.height / 2.0;
	sprite_dimentions.bottom =
		(double)data->screen.height / 2.0 + (double)sprite_dimentions.height / 2.0;
	sprite_dimentions.width = abs_value(floor((double)data->screen.height / transform.y));

	int start_x = -sprite_dimentions.width / 2 + sprite_screen_x;
	int end_x = sprite_dimentions.width / 2 + sprite_screen_x;

	int x = start_x;
	int y;
	sprite_dimentions.top = sprite_dimentions.top < 0 ? 0 : sprite_dimentions.top;
	while(x < end_x)
	{
		if(transform.y > 0 && x > 0 && x < data->screen.width)
		{
			y = sprite_dimentions.top;
			while(y < sprite_dimentions.bottom)
			{
				texture_pos.x =
					((float)(x - start_x) / (float)(end_x - start_x)) * data->textures[SP].width;
				texture_pos.y = (float)(y - sprite_dimentions.top) /
								(float)(sprite_dimentions.bottom - sprite_dimentions.top) *
								data->textures[SP].height;
				if(y < 0 || y >= data->screen.height || x < 0 || x >= data->screen.width)
					return;
				if(texture_pos.x < 0 || texture_pos.y < 0)
					return;
				if(texture_pos.x >= data->textures[SP].width ||
				   texture_pos.y >= data->textures[SP].height)
					return;
				color = get_pixel_color(&data->textures[SP], texture_pos.x, texture_pos.y);
				if((unsigned int)color != 0xff000000)
					my_mlx_pixel_put(&data->img, x, y, color);
				++y;
			}
		}
		++x;
	}
}

void draw_sprites(t_data *data, t_sprite *sprites, int size)
{
	int i = 0;
	while(i < size)
	{
		draw_sprite(data, sprites[i]);
		++i;
	}
}

t_sprite find_sprites(t_data *data, double ray_angle)
{
	t_sprite hor;
	t_sprite ver;

	hor = find_sprite_horizontal_line(data, ray_angle);
	ver = find_sprite_vertical_line(data, ray_angle);
	// t_sprite closest = find_closest_sprite(data->worldMap, hor, ver, data->player);
	// if(is_valid_grid_position(data->worldMap, closest.grid_pos))
	// 	printf("found sprite at (%d, %d)\n", closest.grid_pos.x, closest.grid_pos.y);
	return (find_closest_sprite(data->worldMap, hor, ver, data->player));
}
