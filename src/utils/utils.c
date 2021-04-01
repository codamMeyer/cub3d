#include <math.h>
#include <mlx.h>
#include <utils/utils.h>
#include <utils/defs.h>

void my_mlx_pixel_put(t_img *img, int x, int y, t_color color)
{
	char *dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

// void draw_square(t_img *img, int size, int start_x, int start_y, int color)
// {
// 	for(int i = start_x; i < start_x + size; i++)
// 	{
// 		for(int j = start_y; j < start_y + size; j++)
// 		{
// 			my_mlx_pixel_put(img, i, j, color);
// 		}
// 	}
// }
