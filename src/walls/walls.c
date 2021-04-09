#include "walls.h"
#include <game/render.h>
#include <math.h>
#include <raycast/horizontal_detection.h>
#include <raycast/raycast_utils.h>
#include <raycast/raycast_utils2.h>
#include <raycast/vertical_detection.h>
#include <utils/math_utils.h>

static t_position find_wall(t_map worldMap, double x_increment, double y_increment, t_position ray)
{
	while (!detect_hit(worldMap, ray, WALL))
	{
		ray.x += x_increment;
		ray.y += y_increment;
	}
	return (ray);
}

static void
find_closest_wall(t_position h_intersection, t_position v_intersection, t_player player, t_ray *ray)
{
	const double v_dist = get_distance_from_player(v_intersection, player.position);
	const double h_dist = get_distance_from_player(h_intersection, player.position);
	const double angle = fix_angle(player.angle - ray->angle);

	if (v_dist < h_dist)
	{
		ray->pos = v_intersection;
		ray->distance = fix_fisheye_effect(v_dist, angle);
		ray->orientation = VERTICAL;
	}
	else
	{
		ray->pos = h_intersection;
		ray->distance = fix_fisheye_effect(h_dist, angle);
		ray->orientation = HORIZONTAL;
	}
}

static t_position find_wall_vertical_line(t_data *data, double ray_angle)
{
	t_position ray;
	if (is_up_or_down(ray_angle))
		return (create_invalid_position());
	double tan_angle = tan(degree_to_radians(ray_angle));
	double x_increment = get_x_increment_for_vertical_detection(ray_angle);
	double y_increment = get_y_increment_for_vertical_detection(ray_angle, tan_angle);
	ray = get_first_vertical_intersection(data->player, ray_angle, tan_angle);
	return (find_wall(data->worldMap, x_increment, y_increment, ray));
}

static t_position find_wall_horizontal_line(t_data *data, double ray_angle)
{
	t_position ray;
	if (is_left_or_right(ray_angle))
		return (create_invalid_position());
	double tan_angle = tan(degree_to_radians(ray_angle));
	double y_increment = get_y_increment_for_horizontal_detection(ray_angle);
	double x_increment = get_x_increment_for_horizontal_detection(ray_angle, tan_angle);
	ray = get_first_horizontal_intersection(data->player, ray_angle, tan_angle);
	return (find_wall(data->worldMap, x_increment, y_increment, ray));
}

double find_and_draw_walls(int col, t_data *data, t_ray *ray)
{
	ray->angle = fix_angle(ray->angle);

	t_position h_intersection = find_wall_horizontal_line(data, ray->angle);
	t_position v_intersection = find_wall_vertical_line(data, ray->angle);
	find_closest_wall(h_intersection, v_intersection, data->player, ray);
	draw_slice(data, col, ray);
	return (ray->distance);
}