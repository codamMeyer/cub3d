#include <math.h>
#include <math_utils.h>
#include <ray_casting_logic.h>
#include <sprite.h>
#include <stdio.h>

static t_bool hit_sprite(t_map worldMap, t_position pos)
{
	t_grid_position grid_pos = to_grid_position(worldMap, pos);
	if(grid_pos.x == INVALID || grid_pos.y == INVALID)
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
	if(sprite.grid_pos.y > worldMap.height || sprite.grid_pos.x > worldMap.width)
		printf("aaaaaaaaaaaaa");
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

t_sprite find_closest_sprite(t_sprite horizontal, t_sprite vertical, t_player player)
{
	if(horizontal.center.x > 0 || horizontal.center.y > 0)
	{
		const double h_dist = get_sprite_distance(horizontal.center, player.position);
		if(vertical.center.x > 0 || vertical.center.y > 0)
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

void find_sprites(t_data *data, double ray_angle)
{
	t_sprite hor;
	t_sprite ver;
	t_sprite closest;

	hor = find_sprite_horizontal_line(data, ray_angle);
	ver = find_sprite_vertical_line(data, ray_angle);

	if((hor.center.x > 0 && hor.center.y > 0) || (ver.center.x > 0 && ver.center.y > 0))
	{
		closest = find_closest_sprite(hor, ver, data->player);
		printf("%.2f (%d, %d) | center (%.2f, %.2f)\n",
			   ray_angle,
			   closest.grid_pos.x,
			   closest.grid_pos.y,
			   closest.center.x,
			   closest.center.y);
	}
	else
	{
		printf("no sprite\n");
	}
}
