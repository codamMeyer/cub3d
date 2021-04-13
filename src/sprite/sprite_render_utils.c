#include "sprite_render_utils.h"
#include <math.h>
#include <utils/angle_utils.h>

double	get_sprite_screen_center(double dist_to_plane,
								double sprite_to_player_angle,
								double player_angle,
								double sprite_angle)
{
	double	sprite_screen_center;

	sprite_screen_center = dist_to_plane * \
					tan(degree_to_radians(sprite_to_player_angle));
	if (player_angle > sprite_angle)
		sprite_screen_center *= -1;
	return (sprite_screen_center);
}

double	get_sprite_angle(t_player player, t_sprite sprite)
{
	const t_position	delta = {.x = sprite.center.x - player.position.x,
							  .y = sprite.center.y - player.position.y};
	const double		sprite_angle = \
		fix_angle(radians_to_degrees(atan2(-delta.y, delta.x)));

	return (sprite_angle);
}

t_texture_position	get_texture_position(const t_texture *texture,
												t_dimensions dimensions,
												int y_index,
												double x)
{
	const double		texture_to_sprite_ratio = (double)texture->height / \
												(double)dimensions.real_height;
	const int			wall_pixel_position = (y_index - dimensions.real_top);
	t_texture_position	pos;

	pos.y = floor(wall_pixel_position * texture_to_sprite_ratio);
	pos.x = (int)x * texture_to_sprite_ratio;
	return (pos);
}

t_bool	is_visible(t_sprite_projection sprite, int col, double dist_to_wall)
{
	return (sprite.dist_from_player < dist_to_wall && \
			sprite.dist_from_player < dist_to_wall && sprite.dist_from_player > 0.0 &&\
			col >= sprite.start.x && col <= sprite.end.x);
}
