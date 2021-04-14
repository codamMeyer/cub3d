#include "sprite.h"
#include <math.h>
#include <raycast/horizontal_detection.h>
#include <raycast/raycast_utils.h>
#include <raycast/vertical_detection.h>
#include <render/render_utils.h>
#include <utils/angle_utils.h>
#include <utils/direction.h>
#include <utils/grid_position.h>
#include <utils/math_utils.h>
#include <stdio.h>

static t_bool	swap(t_sprite *cur, t_sprite *prev)
{
	t_sprite	tmp;

	if (cur->dist_from_player > prev->dist_from_player)
	{
		tmp = *cur;
		*cur = *prev;
		*prev = tmp;
		return (TRUE);
	}
	return (FALSE);
}

void	sort_sprites(t_sprite *sprites, int sprite_count)
{
	t_bool	swapped;
	int		i;

	if (sprite_count <= 1)
		return ;
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

t_grid_position	create_invalid_grid_pos(void)
{
	const t_grid_position	pos = {.x = INVALID, .y = INVALID};

	return (pos);
}

int	add_sprites_to_array(t_map worldMap,
						t_sprite *sprites,
						t_intersections intersections)
{
	int				count;

	count = 0;
	while (is_valid_position(worldMap, intersections.horizontal) || \
		   is_valid_position(worldMap, intersections.vertical))
	{
		if (detect_hit(worldMap, intersections.horizontal, SPRITE))
		{
			sprites[count].center = compute_grid_center(worldMap, intersections.horizontal);
			++count;
		}
		if (detect_hit(worldMap, intersections.vertical, SPRITE))
		{
			sprites[count].center = compute_grid_center(worldMap, intersections.vertical);
			++count;
		}
		if (count > 1 && \
			is_same_pos(sprites[count].center, sprites[count - 1].center))
			--count;
		apply_incremento_to_intersections(&intersections);
	}
	return (count);
}

int	find_sprites(t_player player,
				t_map worldMap,
				t_sprite *sprites,
				double angle)
{
	const double			tan_angle = tan(degree_to_radians(angle));
	const t_intersections	intersections = {
	.hor_increment = get_horizontal_detection_increment(angle, tan_angle),
	.ver_increment = get_vertical_detection_increment(angle, tan_angle),
	.horizontal = get_first_horizontal_intersection(player, angle, tan_angle),
	.vertical = get_first_vertical_intersection(player, angle, tan_angle),
	};

	return (add_sprites_to_array(worldMap, sprites, intersections));
}
