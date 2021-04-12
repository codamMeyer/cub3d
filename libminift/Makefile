NAME = libminift.a
HEADER_FILES = libminift.h
CC=gcc
CFLAGS= -Wall -Werror -Wextra -O3
LDFLAGS= -shared -fPIC
CREATE_LIB=ar rcs

SRC_FILES=					\
	ft_strlen.c     		\
	ft_atoi.c       		\
	ft_strncmp.c    		\
	ft_strcpy.c	    		\
	ft_split.c      		\
	ft_memcpy.c				\
	ft_isdigit.c			\
	get_next_line.c			\
	get_next_line_utils.c	\
	
	

SRC_OBJ = $(SRC_FILES:.c=.o)
OBJ_FILES = $(SRC_OBJ)

all: $(NAME)

$(NAME): $(OBJ_FILES)
	ar rc $@ $^
	ranlib $@

%.o: %.c $(HEADER_FILES)
	$(CC) -c $(CFLAGS) -o $@ $<

clean:
	rm -f $(SRC_OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re