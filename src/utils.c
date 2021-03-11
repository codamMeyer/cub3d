#include <defs.h>
#include <math.h>
#include <mlx.h>
#include <utils.h>

void my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char *dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int paint_background(int w, int h, t_data *data)
{
	int x;
	int y;
	int color;

	x = w;
	while(x--)
	{
		y = h;
		while(y--)
		{
			color = YELLOW;
			my_mlx_pixel_put(&data->map, x, y, color);
		}
	}
	mlx_put_image_to_window(data->mlx, data->window, data->map.img, 0, 0);
	return (0);
}

void draw_square(t_img *img, int size, int start_x, int start_y, int color)
{
	for(int i = start_x; i < start_x + size; i++)
	{
		for(int j = start_y; j < start_y + size; j++)
		{
			my_mlx_pixel_put(img, i, j, color);
		}
	}
}
