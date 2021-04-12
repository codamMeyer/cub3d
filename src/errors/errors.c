#include "errors.h"
#include <libft.h>
#include <stdio.h>
#include <unistd.h>
void print_error_message(t_status status)
{
	const char *status_message[14] = {
		"Success\n",
		"Failed to read file\n",
		"Incorrect file extension, expected filename.cub\n",
		"Inavlid resolution\n",
		"Missing information about texture\n",
		"Invalid Color, expected RGB\n",
		"Map not found\n",
		"Map possible chars: \n0:empty\n1:wall\n2:item\n[N,S,E,W]:player\n",
		"Map isn't surrounded by walls\n",
		"Missing or more than player position\n",
		"Error while loading texture\n",
		"Malloc error\n",
		"Usage: ./raycaster <map_path> [--save]\n",
		"Error while initializing window\n",
	};
	const int len = ft_strlen(status_message[(int)status]);
	const char *error = "Error\n";

	write(STDERR_FILENO, error, 6);
	write(STDERR_FILENO, status_message[(int)status], len);
}