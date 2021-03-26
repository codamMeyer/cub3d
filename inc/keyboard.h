#ifndef KEYBOARD_H
#define KEYBOARD_H
// KEYS

#define ESC 65307
#define W_KEY 119
#define S_KEY 115
#define A_KEY 97
#define D_KEY 100
#define LEFT 65361
#define RIGHT 65363

#include "defs.h"

int keypressed(int keycode, t_data *data);

#endif