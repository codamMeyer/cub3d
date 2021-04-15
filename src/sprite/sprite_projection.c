#include "sprite_projection.h"
#include <math.h>
#include <raycast/horizontal_detection.h>
#include <raycast/raycast_utils.h>
#include <raycast/vertical_detection.h>
#include <render/render_utils.h>
#include <utils/angle_utils.h>
#include <utils/direction.h>
#include <utils/grid_position.h>
#include <utils/math_utils.h>
#include "sprite_render_utils.h"

void	get_sprite_projection(t_player player,
							t_window screen,
							t_sprite *sprite)
{
	const double		sprite_angle = \
						get_sprite_angle(player.position, sprite->center);
	const double		sprite_to_player_angle = \
							abs_value(sprite_angle - player.angle);
	const double		sprite_screen_center = \
							get_sprite_screen_center(player.dist_to_plane, \
													sprite_to_player_angle, \
													player.angle, \
													sprite_angle);
	const double		sp_screen_x = (double)screen.width / 2.0 \
											- sprite_screen_center;

	sprite->dist_from_player = fix_fisheye_effect(sprite->dist_from_player, \
												sprite_to_player_angle);
	sprite->dimensions = \
		get_dimensions(sprite->dist_from_player, player, screen);
	sprite->start.y = ((double)screen.height / 2.0) - \
					((double)sprite->dimensions.height / 2.0);
	sprite->end.y = sprite->start.y + screen.height;
	sprite->start.x = sp_screen_x - ((double)sprite->dimensions.width / 2.0);
	sprite->end.x = sprite->start.x + sprite->dimensions.width;
}

t_bool	in_sprites_list(t_sprite *sprites, t_position center, int index)
{
	int	i;

	i = 0;
	while (i < index)
	{
		if (is_same_pos(sprites[i].center, center))
			return (TRUE);
		++i;
	}
	return (FALSE);
}

void	swap(t_sprite *cur, t_sprite *prev)
{
	const t_sprite	tmp = *cur;

	*cur = *prev;
	*prev = tmp;
}

void	sort(t_sprite *sprites, int sprite_count)
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
			if (sprites[i].dist_from_player > sprites[i - 1].dist_from_player)
			{
				swapped = TRUE;
				swap(&sprites[i], &sprites[i - 1]);
			}
			++i;
		}
	}
}

t_intersections	create_intersections(t_player player, double angle)
{
	const double			tan_angle = tan(degree_to_radians(angle));
	const t_intersections	intersections = {
	.hor_increment = get_horizontal_detection_increment(angle, tan_angle),
	.ver_increment = get_vertical_detection_increment(angle, tan_angle),
	.horizontal = get_first_horizontal_intersection(player, angle, tan_angle),
	.vertical = get_first_vertical_intersection(player, angle, tan_angle),
	};

	return (intersections);
}
