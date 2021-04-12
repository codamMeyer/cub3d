#include "game/keyboard.h"
#include <mlx.h>
#include <player/player.h>
#include <stdlib.h>

int	keypressed(int keycode, t_data *data)
{
	if (keycode == ESC)
		close_window(data);
	else if (keycode == W_KEY)
		move_forward(&data->player, data->worldMap);
	else if (keycode == S_KEY)
		move_backward(&data->player, data->worldMap);
	else if (keycode == A_KEY)
		move_left(&data->player, data->worldMap);
	else if (keycode == D_KEY)
		move_right(&data->player, data->worldMap);
	else if (keycode == LEFT)
		turn_counterclockwise(&data->player);
	else if (keycode == RIGHT)
		turn_clockwise(&data->player);
	return (0);
}
