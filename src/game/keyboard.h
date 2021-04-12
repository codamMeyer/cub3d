#ifndef KEYBOARD_H
# define KEYBOARD_H
# define KEY_PRESS_EVENT 2
# define CLIENT_MSG_EVENT 33
# include "game.h"
# include <player/player.h>
# include <utils/defs.h>

typedef enum e_key
{
	W_KEY = 119,
	S_KEY = 115,
	A_KEY = 97,
	D_KEY = 100,
	LEFT = 65361,
	RIGHT = 65363,
	ESC = 65307,
}	t_key;

int	keypressed(int keycode, t_data *data);

#endif