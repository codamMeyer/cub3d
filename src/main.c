#include <bmp/bmp.h>
#include <errors/errors.h>
#include <game/game.h>
#include <libminift.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
	t_status error;
	t_bool save;

	save = FALSE;
	if (argc < 2 || argc > 3)
	{
		print_error_message(ARG_ERROR);
		return (1);
	}
	if (argc == 3 && (ft_strncmp("--save", argv[2], 7) == 0))
		save = TRUE;
	error = run(argv[1], save);
	if (error)
	{
		print_error_message(error);
		return (1);
	}
	return (0);
}
