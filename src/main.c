#include <game/game.h>
#include <utils/errors.h>

int main(int argc, char *argv[])
{
	t_status error;

	if(argc < 2 || argc > 3)
	{
		print_error_message(ARG_ERROR);
		return (1);
	}
	error = run(argv[1]);
	if(error)
	{
		print_error_message(error);
		return (1);
	}
	return (0);
}