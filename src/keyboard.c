#include <keyboard.h>
#include <map.h>
#include <math.h>
#include <mlx.h>
#include <player.h>
#include <raycaster.h>
#include <stdlib.h>
#include <utils.h>

int keypress(int keycode, t_data *data)
{
	if(keycode == ESC)
	{
		free_matrix(data->worldMap.matrix, mapHeight);
		mlx_destroy_window(data->mlx, data->window);
		exit(0);
	}
	else if(keycode == UP)
		move_forward(&data->player, data);
	// else if(keycode == DOWN)
	// {
	// 	if(!check_wall_hit(data,
	// 					   floor(data->player.position.x),
	// 					   floor(data->player.position.y) + data->player.speed +
	// 						   data->player.size / 2))

	// 	{
	// 		data->player.position.y +=
	// 			sin(degree_to_radians(data->player.angle)) * data->player.speed;
	// 		data->player.position.x -=
	// 			cos(degree_to_radians(data->player.angle)) * data->player.speed;
	// 	}
	// }
	else if(keycode == LEFT)
	{
		if(data->player.angle >= 360)
			data->player.angle = 0;
		data->player.angle += 1.5;
	}
	else if(keycode == RIGHT)
	{
		if(data->player.angle <= 0)
			data->player.angle = 360;
		data->player.angle -= 1.5;
	}
	return (0);
}