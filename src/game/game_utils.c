#include "game_utils.h"
#include <mlx.h>
#include <utils/map_utils.h>
#include <stdlib.h>

static void	cleanup(t_data *data)
{
	free_matrix(data->worldMap.matrix, data->worldMap.height);
	free(data->sprites);
}

void	close_window(t_data *data, t_status status)
{
	if (status != SUCCESS)
		print_error_message(status);
	if (data->worldMap.matrix != NULL)
		cleanup(data);
	if (data->img.mlx != NULL)
		mlx_destroy_window(data->img.mlx, data->img.window);
	exit(0);

}

int	red_cross(t_data *data, t_status status)
{
	close_window(data, status);
	return (1);
}

t_texture	load_texture(t_data *data, char *filename)
{
	t_texture	texture;
	int			endian;

	endian = 0;
	texture.initialized = FALSE;
	texture.ptr = mlx_xpm_file_to_image(data->img.mlx, filename, \
										&(texture.width), &(texture.height));
	if (!texture.ptr)
		return (texture);
	texture.data = mlx_get_data_addr(texture.ptr, &texture.bit_per_pixel, \
							&texture.line_size, &endian);
	texture.initialized = TRUE;
	return (texture);
}
