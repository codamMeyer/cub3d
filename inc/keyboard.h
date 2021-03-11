#ifndef KEYBOARD_H
#define KEYBOARD_H
// KEYS

#define ESC 65307
#define UP 65362
#define DOWN 65364
#define LEFT 65361
#define RIGHT 65363

#include "defs.h"

int keypressed(int keycode, t_data *data);

#endif