#ifndef LIBFT_H
# define LIBFT_H
# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# define LONG_MAX 9223372036854775807
# define MAX_FD 2048
# define SIZE 500
# define ERROR -1
# define LINE_READ 1

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

typedef int	t_bool;

typedef struct s_file_state
{
	char	buffer[BUFFER_SIZE];
	int		buffer_index;
	int		bytes_left;
	int		line_index;
	int		line_size;
}	t_file_state;

void	*ft_realloc(void *ptr, size_t prev_size, size_t new_size);
int		adjust_mem_size(t_file_state *f_state, char **dest);
int		realloc_line(char **dest, t_file_state **file_state, int *ret);
int		ft_strlen(const char *str);
int		ft_atoi(const char *nptr);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	ft_strcpy(char *dest, char *src);
char	**ft_split(char const *s, char c);
void	*ft_memcpy(void *dest, const void *src, size_t n);
int		ft_isdigit(int c);
int		get_next_line(int fd, char **line);
char	*ft_strtrim(char const *s1, char const *set);
void	*ft_calloc(size_t nmemb, size_t size);
void	ft_bzero(void *s, size_t n);

#endif
