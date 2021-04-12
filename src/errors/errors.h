#ifndef ERRORS_H
# define ERRORS_H
# include <utils/defs.h>

typedef enum e_status
{
	SUCCESS = 0,
	FILE_ERROR,
	EXTENSION_ERROR,
	RESOLUTION_ERROR,
	TEXTURE_INFO_ERROR,
	COLOR_ERROR,
	MISSING_MAP_ERROR,
	MAP_CONTENT_ERROR,
	MAP_NOT_SURROUNDED_ERROR,
	PLAYER_INIT_ERROR,
	LOAD_ERROR,
	MALLOC_ERROR,
	ARG_ERROR,
	INIT_WINDOW_ERROR,
}	t_status;

void	print_error_message(t_status status);

#endif