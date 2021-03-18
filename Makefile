NAME=raycaster
CC=clang
CFLAGS= -ggdb3 -Wall -Wextra -Werror -fsanitize=address -fsanitize=leak
TEST_CFLAGS= -ggdb3 -Wall -Wextra -Werror #-fsanitize=address -fsanitize=leak
INC_PATH=-I./mlx_linux -I./inc -I./
LDFLAGS=-L./mlx_linux -lmlx -L./ -lXext -lX11 -lm -lz

SRC_FILES=						\
	src/raycaster.c 			\
	src/keyboard.c				\
	src/map.c	    			\
	src/player.c				\
	src/utils.c  				\
	src/math_utils.c  			\
	src/direction.c  			\
	src/ray_casting_logic.c		\
	src/render.c

INC_FILES=						\
	inc/raycaster.h  			\
	inc/keyboard.h	 			\
	inc/map.h	     			\
	inc/player.h	 			\
	inc/utils.h  	 			\
	inc/math_utils.h 			\
	inc/direction.h  			\
	inc/ray_casting_logic.h		\
	inc/render.h

TEST_FILES= 								\
	test/main.c 							\
	test/test_horizontal_lines_detection.c 	\
	test/test_vertical_lines_detection.c 	\
	test/test_player_forward_move.c			\
	test/test_player_backward_move.c		\
	test/test_wall_distance.c				\
	test/test_intersection.c				\
	test/test_find_closer_wall.c

all: $(NAME)

$(NAME): $(INC_FILES) $(SRC_FILES)
	$(CC) $(CFLAGS) $(INC_PATH) $(SRC_FILES) src/main.c $(LDFLAGS) -o $(NAME)

test: $(INC_FILES) $(SRC_FILES) $(TEST_FILES)
	$(CC) $(TEST_CFLAGS) $(INC_PATH) $(SRC_FILES) $(TEST_FILES) $(LDFLAGS) -o tester

clean:
	rm -f $(SRC_OBJ)

re: fclean all

fclean: clean
	rm -f $(NAME)

.PHONY: all clean fclean re test
