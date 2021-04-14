#ifndef KEYBOARD_H
# define KEYBOARD_H
# define KEY_PRESS_EVENT 2
# define KEY_RELEASE_EVENT 3
# define CLIENT_MSG_EVENT 33
# include "game.h"

typedef enum e_key
{
	W_KEYCODE = 119,
	S_KEYCODE = 115,
	A_KEYCODE = 97,
	D_KEYCODE = 100,
	LEFT_ARROW_KEYCODE = 65361,
	RIGHT_ARROW_KEYCODE = 65363,
	ESC_KEYCODE = 65307,
}	t_key;

int	key_pressed(int keycode, t_data *data);
int	key_released(int keycode, t_data *data);

#endif