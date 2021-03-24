# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    MakefileSub                                        :+:    :+:             #
#                                                      +:+                     #
#    By: mmeyer <mmeyer@student.codam.nl>             +#+                      #
#                                                    +#+                       #
#    Created: 2020/11/10 14:32:36 by mmeyer        #+#    #+#                  #
#    Updated: 2021/01/30 16:41:53 by mmeyer        ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
HEADER_FILES = libft.h
CC=gcc
CFLAGS= -Wall -Werror -Wextra
CREATE_LIB=ar rcs

SRC_FILES= \
	ft_isalpha.c    \
 	ft_isdigit.c    \
  	ft_isalnum.c    \
	ft_isascii.c    \
	ft_isprint.c    \
	ft_toupper.c    \
	ft_tolower.c    \
	ft_strlen.c     \
	ft_atoi.c       \
	ft_strncmp.c    \
	ft_strlcat.c    \
	ft_strlcpy.c    \
	ft_strcpy.c    \
	ft_strdup.c     \
	ft_strjoin.c    \
	ft_memset.c     \
	ft_bzero.c      \
	ft_memcpy.c     \
	ft_memccpy.c    \
	ft_memmove.c    \
	ft_memcmp.c     \
	ft_memchr.c     \
	ft_strchr.c     \
	ft_strrchr.c    \
	ft_strnstr.c    \
	ft_calloc.c     \
	ft_substr.c     \
	ft_strtrim.c    \
	ft_split.c      \
	ft_itoa.c       \
	ft_strmapi.c    \
	ft_putchar_fd.c \
	ft_putstr_fd.c  \
	ft_putnstr_fd.c  \
	ft_putendl_fd.c \
	ft_putnbr_fd.c

BONUS_FILES = \
	ft_lstadd_back.c  \
	ft_lstadd_front.c \
	ft_lstclear.c     \
	ft_lstdelone.c    \
	ft_lstiter.c      \
	ft_lstlast.c      \
	ft_lstnew.c       \
	ft_lstsize.c      \
	ft_lstmap.c

SRC_OBJ = $(SRC_FILES:.c=.o)
BONUS_OBJ= $(BONUS_FILES:.c=.o)

ifdef WITH_BONUS
OBJ_FILES = $(SRC_OBJ) $(BONUS_OBJ)
else
OBJ_FILES = $(SRC_OBJ)
endif

all: $(NAME)

$(NAME): $(OBJ_FILES)
	ar rc $@ $^
	ranlib $@

%.o: %.c $(HEADER_FILES)
	$(CC) -c $(CFLAGS) -o $@ $<

bonus:
	$(MAKE) WITH_BONUS=1 all

clean:
	rm -f $(SRC_OBJ) $(BONUS_OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
