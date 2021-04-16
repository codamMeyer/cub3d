#include "game_utils.h"
#include "keyboard.h"

int	key_pressed(int keycode, t_data *data)
{
	if (keycode == ESC_KEYCODE)
		close_window(data, SUCCESS);
	else if (keycode == W_KEYCODE)
		data->player.direction = FORWARD;
	else if (keycode == S_KEYCODE)
		data->player.direction = BACKWARD;
	else if (keycode == A_KEYCODE)
		data->player.direction = LEFT;
	else if (keycode == D_KEYCODE)
		data->player.direction = RIGHT;
	else if (keycode == LEFT_ARROW_KEYCODE)
		data->player.rotation = COUNTERCLOCKWISE;
	else if (keycode == RIGHT_ARROW_KEYCODE)
		data->player.rotation = CLOCKWISE;
	return (0);
}

int	key_released(int keycode, t_data *data)
{
	if (keycode == W_KEYCODE)
		data->player.direction = STILL;
	else if (keycode == S_KEYCODE)
		data->player.direction = STILL;
	else if (keycode == A_KEYCODE)
		data->player.direction = STILL;
	else if (keycode == D_KEYCODE)
		data->player.direction = STILL;
	else if (keycode == LEFT_ARROW_KEYCODE || keycode == RIGHT_ARROW_KEYCODE)
		data->player.rotation = NONE;
	return (0);
}
