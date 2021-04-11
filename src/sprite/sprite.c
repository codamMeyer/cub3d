#include "sprite.h"
#include <assert.h>
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

// void add_sprites_to_list(t_map worldMap, t_list **sprites, t_position increment, t_position ray)
// {
// 	t_sprite *sprite;
// 	t_bool hit = FALSE;
// 	t_grid_position grid_pos;

// 	while (TRUE)
// 	{
// 		hit = hit_sprite(worldMap, ray);
// 		if (hit == INVALID)
// 			break;
// 		if (hit)
// 		{
// 			sprite = malloc(sizeof(t_sprite));
// 			grid_pos = to_grid_position(worldMap, ray);
// 			sprite->center = get_grid_center(grid_pos);
// 			t_list *new_element = ft_lstnew(sprite);
// 			ft_lstadd_front(sprites, new_element);
// 		}
// 		ray.x += increment.x;
// 		ray.y += increment.y;
// 	}
// }

// void find_sprite_list_horizontal_line(t_player player,
// 									  t_map worldMap,
// 									  t_sprite *sprites,
// 									  double ray_angle)
// {
// 	const double tan_angle = tan(degree_to_radians(ray_angle));
// 	const t_position increment = get_increment_for_horizontal_detection(ray_angle, tan_angle);
// 	t_position pos;

// 	pos = get_first_horizontal_intersection(player, ray_angle, tan_angle);
// 	add_sprites_to_list(worldMap, sprites, increment, pos);
// }

// void find_sprite_list_vertical_line(t_player player,
// 									t_map worldMap,
// 									t_sprite *sprites,
// 									double ray_angle)
// {
// 	const double tan_angle = tan(degree_to_radians(ray_angle));
// 	const t_position increment = get_increment_for_vertical_detection(ray_angle, tan_angle);
// 	t_position pos;

// 	pos = get_first_vertical_intersection(player, ray_angle, tan_angle);
// 	add_sprites_to_list(worldMap, sprites, increment, pos);
// }

static t_bool is_valid_grid(t_grid_position pos)
{
	return (pos.x != INVALID && pos.y != INVALID);
}

t_grid_position create_invalid_grid_pos()
{
	const t_grid_position pos = {.x = INVALID, .y = INVALID};

	return (pos);
}

int add_sprites_to_array(t_map worldMap,
						 t_sprite *sprites,
						 t_position horizontal_increment,
						 t_position horizontal_intersection,
						 t_position vertical_increment,
						 t_position vertical_intersection)
{
	int sprite_count = 0;
	t_bool hor_hit = FALSE;
	t_bool ver_hit = FALSE;
	t_grid_position hor_grid_pos;
	t_grid_position ver_grid_pos;

	while (TRUE)
	{
		assert(sprite_count <= 11);
		hor_grid_pos = create_invalid_grid_pos();
		ver_grid_pos = create_invalid_grid_pos();
		hor_hit = hit_sprite(worldMap, horizontal_intersection);
		ver_hit = hit_sprite(worldMap, vertical_intersection);
		if (hor_hit == INVALID && ver_hit == INVALID)
			break;
		if (hor_hit == TRUE)
			hor_grid_pos = to_grid_position(worldMap, horizontal_intersection);
		if (ver_hit == TRUE)
			ver_grid_pos = to_grid_position(worldMap, vertical_intersection);
		if (is_valid_grid(hor_grid_pos) && is_valid_grid(ver_grid_pos))
		{
			if ((hor_grid_pos.x != ver_grid_pos.x) && (hor_grid_pos.y != ver_grid_pos.y))
			{
				sprites[sprite_count].center = get_grid_center(hor_grid_pos);
				++sprite_count;
				sprites[sprite_count].center = get_grid_center(ver_grid_pos);
				++sprite_count;
			}
			else
			{
				sprites[sprite_count].center = get_grid_center(hor_grid_pos);
				++sprite_count;
			}
		}
		else
		{
			if (is_valid_grid(hor_grid_pos))
			{
				sprites[sprite_count].center = get_grid_center(hor_grid_pos);
				++sprite_count;
			}
			else if (is_valid_grid(ver_grid_pos))
			{
				sprites[sprite_count].center = get_grid_center(ver_grid_pos);
				++sprite_count;
			}
		}
		horizontal_intersection.x += horizontal_increment.x;
		horizontal_intersection.y += horizontal_increment.y;
		vertical_intersection.x += vertical_increment.x;
		vertical_intersection.y += vertical_increment.y;
	}
	return (sprite_count);
}

int find_sprite_list(t_player player, t_map worldMap, t_sprite *sprites, double ray_angle)
{
	const double tan_angle = tan(degree_to_radians(ray_angle));
	const t_position horizontal_increment =
		get_increment_for_horizontal_detection(ray_angle, tan_angle);
	const t_position vertical_increment =
		get_increment_for_vertical_detection(ray_angle, tan_angle);
	const t_position horizontal_intersection =
		get_first_horizontal_intersection(player, ray_angle, tan_angle);
	const t_position vertical_intersection =
		get_first_vertical_intersection(player, ray_angle, tan_angle);

	return (add_sprites_to_array(worldMap,
								 sprites,
								 horizontal_increment,
								 horizontal_intersection,
								 vertical_increment,
								 vertical_intersection));
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

int find_sprites(t_player player, t_map worldMap, t_sprite *sprites, double ray_angle)
{
	// if (!is_left_or_right(ray_angle))
	// 	find_sprite_list_horizontal_line(player, worldMap, sprites, ray_angle);
	// if (!is_up_or_down(ray_angle))
	return (find_sprite_list(player, worldMap, sprites, ray_angle));
}
