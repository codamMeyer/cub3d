#include "sprite.h"
#include <math.h>
#include <raycast/horizontal_detection.h>
#include <raycast/raycast_utils.h>
#include <raycast/vertical_detection.h>
#include <render/render_utils.h>
#include <utils/angle_utils.h>
#include <utils/direction.h>
#include <utils/math_utils.h>

t_grid_position create_invalid_grid_pos()
{
	const t_grid_position pos = {.x = INVALID, .y = INVALID};

	return (pos);
}

void apply_incremento_to_intersections(t_intersections *intersections)
{
	intersections->horizontal.x += intersections->hor_increment.x;
	intersections->horizontal.y += intersections->hor_increment.y;
	intersections->vertical.x += intersections->ver_increment.x;
	intersections->vertical.y += intersections->ver_increment.y;
}

int add_sprites_to_array(t_map worldMap, t_sprite *sprites, t_intersections intersections)
{
	int sprite_count = 0;
	t_grid_position grid_pos;

	while (is_valid_position(worldMap, intersections.horizontal) ||
		   is_valid_position(worldMap, intersections.vertical))
	{
		if (detect_hit(worldMap, intersections.horizontal, SPRITE))
		{
			grid_pos = to_grid_position(worldMap, intersections.horizontal);
			sprites[sprite_count].center = get_grid_center(grid_pos);
			++sprite_count;
		}
		if (detect_hit(worldMap, intersections.vertical, SPRITE))
		{
			grid_pos = to_grid_position(worldMap, intersections.vertical);
			sprites[sprite_count].center = get_grid_center(grid_pos);
			++sprite_count;
		}
		if (sprite_count > 1 &&
			is_same_pos(sprites[sprite_count].center, sprites[sprite_count - 1].center))
			--sprite_count;
		apply_incremento_to_intersections(&intersections);
	}
	return (sprite_count);
}

int find_sprites(t_player player, t_map worldMap, t_sprite *sprites, double ray_angle)
{
	const double tan_angle = tan(degree_to_radians(ray_angle));
	const t_intersections intersections = {
		.hor_increment = get_increment_for_horizontal_detection(ray_angle, tan_angle),
		.ver_increment = get_increment_for_vertical_detection(ray_angle, tan_angle),
		.horizontal = get_first_horizontal_intersection(player, ray_angle, tan_angle),
		.vertical = get_first_vertical_intersection(player, ray_angle, tan_angle),
	};

	return (add_sprites_to_array(worldMap, sprites, intersections));
}

static t_bool swap(t_sprite *cur, t_sprite *prev)
{
	t_sprite tmp;

	if (cur->dist_from_player > prev->dist_from_player)
	{
		tmp = *cur;
		*cur = *prev;
		*prev = tmp;
		return (TRUE);
	}
	return (FALSE);
}

void sort_sprites(t_sprite *sprites, int sprite_count)
{
	t_bool swapped;
	int i;

	if (sprite_count <= 1)
		return;
	swapped = TRUE;
	while (swapped)
	{
		swapped = FALSE;
		i = 1;
		while (i < sprite_count)
		{
			swapped = swap(&sprites[i], &sprites[i - 1]);
			++i;
		}
	}
}
