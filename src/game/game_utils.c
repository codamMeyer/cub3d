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
	exit(status);
}

int	red_cross(t_data *data, t_status status)
{
	close_window(data, status);
	return (1);
}

static t_texture	load_texture(t_data *data, char *filename)
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

t_status	load_textures(t_data *data)
{
	data->textures[NO] = load_texture(data, data->textures[NO].filename);
	data->textures[SO] = load_texture(data, data->textures[SO].filename);
	data->textures[WE] = load_texture(data, data->textures[WE].filename);
	data->textures[EA] = load_texture(data, data->textures[EA].filename);
	data->textures[SP] = load_texture(data, data->textures[SP].filename);
	if (!data->textures[NO].initialized || !data->textures[SO].initialized || \
		!data->textures[WE].initialized || !data->textures[EA].initialized || \
		!data->textures[SP].initialized)
		return (TEXTURE_INFO_ERROR);
	return (SUCCESS);
}
