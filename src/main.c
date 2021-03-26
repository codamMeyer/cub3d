#include <raycaster.h>

int main(int argc, char *argv[])
{
	if (argc < 2 || argc > 3)
		return (FALSE);
	run(argv[1]);
}