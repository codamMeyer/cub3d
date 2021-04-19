#include "player.h"

t_player	create_player(void)
{
	const t_player	player = {
								.angle = INVALID_ORIENTATION,
								.FOV = 60,
								.speed = 5,
								.direction = STILL,
								.rotation = NONE,
							};

	return (player);
}
