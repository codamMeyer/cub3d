#ifndef KEYBOARD_H
#define KEYBOARD_H
#define KEY_PRESS_EVENT 2
#define CLIENT_MESSAGE_EVENT 33
#define KEY_PRESS_MASK (1L << 0)
#define STRUCT_NOTIFY_MASK (1L << 17)
#define ESC 65307
#define W_KEY 119
#define S_KEY 115
#define A_KEY 97
#define D_KEY 100
#define LEFT 65361
#define RIGHT 65363
#include "game.h"
#include <player/player.h>
#include <utils/defs.h>

int keypressed(int keycode, t_data *data);

#endif