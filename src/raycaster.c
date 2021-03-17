#include <direction.h>
#include <keyboard.h>
#include <map.h>
#include <mlx.h>
#include <player.h>
#include <ray_casting_logic.h>
#include <raycaster.h>
#include <render.h>
#include <utils.h>

void rayCasting(t_data *data)
{
	double ray_angle = data->player.angle + (data->player.FOV / 2);
	const double ray_increment = (double)data->player.FOV / (double)data->player.plane_x;
	t_position h_intersection;
	t_position v_intersection;
	double closer_wall;
	int color;

	for(int col = 0; col < data->player.plane_x; col++)
	{
		h_intersection = find_horizontal_line(data, ray_angle);
		v_intersection = find_vertical_line(data, ray_angle);
		closer_wall = find_closer_wall(h_intersection, v_intersection, data->player, ray_angle);

		color = RED;
		draw_slice(data, closer_wall, col, color);

		ray_angle -= ray_increment;
	}
	mlx_put_image_to_window(data->mlx, data->window, data->map.img, 0, 0);
}

static int display(t_data *data)
{
	paint_background(screenWidth, screenHeight, data);
	rayCasting(data);
	draw_map_2d(data);
	draw_player(data);
	return (1);
}

void run()
{
	t_data data;

	data.mlx = mlx_init();
	data.window = mlx_new_window(data.mlx, screenWidth, screenHeight, "*** Raycaster ***");
	data.map.img = mlx_new_image(data.mlx, screenWidth, screenHeight);
	data.map.addr = mlx_get_data_addr(
		data.map.img, &data.map.bits_per_pixel, &data.map.line_length, &data.map.endian);
	data.worldMap.height = 25;
	data.worldMap.width = 25;
	data.worldMap.matrix = init_matrix(data.worldMap.height, data.worldMap.width);

	data.worldMap.matrix[3][3] = 1;
	data.worldMap.matrix[3][4] = 1;

	init_player(&data);
	mlx_hook(data.window, 2, 1L << 0, keypressed, &data);
	mlx_loop_hook(data.mlx, display, &data);
	mlx_loop(data.mlx);
}
