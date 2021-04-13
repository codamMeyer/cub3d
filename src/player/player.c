#include "player.h"
#include <math.h>
#include <utils/angle_utils.h>
#include <utils/math_utils.h>

t_player	create_player(void)
{
	const t_player	player = {
								.angle = INVALID_ORIENTATION,
								.FOV = 60,
								.speed = 3,
								.direction = STILL,
								.rotation = NONE,
							};

	return (player);
}
