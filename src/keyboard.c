#include <keyboard.h>
#include <map.h>
#include <math.h>
#include <mlx.h>
#include <player.h>
#include <raycaster.h>
#include <stdlib.h>
#include <utils.h>

static void close_window(t_data *data)
{
	free_matrix(data->worldMap.matrix, data->worldMap.height);
	mlx_destroy_window(data->mlx, data->window);
	exit(0);
}

int keypressed(int keycode, t_data *data)
{
	if(keycode == ESC)
		close_window(data);
	else if(keycode == UP)
		move_forward(&data->player, data);
	else if(keycode == DOWN)
		move_backward(&data->player, data);
	else if(keycode == LEFT)
		turn_counterclockwise(&data->player);
	else if(keycode == RIGHT)
		turn_clockwise(&data->player);
	return (0);
}
