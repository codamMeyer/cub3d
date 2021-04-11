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

int add_sprites_to_array(t_map worldMap,
						 t_sprite *sprites,
						 t_position horizontal_increment,
						 t_position horizontal_intersection,
						 t_position vertical_increment,
						 t_position vertical_intersection)
{
	int sprite_count = 0;
	t_grid_position grid_pos;

	while (is_valid_position(worldMap, horizontal_intersection) ||
		   is_valid_position(worldMap, vertical_intersection))
	{
		if (detect_hit(worldMap, horizontal_intersection, SPRITE))
		{
			grid_pos = to_grid_position(worldMap, horizontal_intersection);
			sprites[sprite_count].center = get_grid_center(grid_pos);
			++sprite_count;
		}
		if (detect_hit(worldMap, vertical_intersection, SPRITE))
		{
			grid_pos = to_grid_position(worldMap, vertical_intersection);
			sprites[sprite_count].center = get_grid_center(grid_pos);
			++sprite_count;
		}
		if (sprite_count > 1 &&
			is_same_pos(sprites[sprite_count].center, sprites[sprite_count - 1].center))
			--sprite_count;
		horizontal_intersection.x += horizontal_increment.x;
		horizontal_intersection.y += horizontal_increment.y;
		vertical_intersection.x += vertical_increment.x;
		vertical_intersection.y += vertical_increment.y;
	}
	return (sprite_count);
}

int find_sprites(t_player player, t_map worldMap, t_sprite *sprites, double ray_angle)
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
