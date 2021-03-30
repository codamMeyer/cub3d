#ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H
#include <stdlib.h>
#include <unistd.h>
#define MAX_FD 2048
#define SIZE 500
#define ERROR -1
#define LINE_READ 1

#ifndef BUFFER_SIZE
#	define BUFFER_SIZE 100
#endif

typedef int t_bool;

typedef struct s_file_state
{
	char buffer[BUFFER_SIZE];
	int buffer_index;
	int bytes_left;
	int line_index;
	int line_size;
} t_file_state;

int get_next_line(int fd, char **line);
void *ft_realloc(void *ptr, size_t prev_size, size_t new_size);
int adjust_mem_size(t_file_state *f_state, char **dest);
int realloc_line(char **dest, t_file_state **file_state, int *ret);

#endif
