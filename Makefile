NAME=raycaster
CC=clang
CFLAGS= -ggdb3 -Wall -Wextra -Werror -fsanitize=address -fsanitize=leak
TEST_CFLAGS= -ggdb3 -Wall -Wextra -Werror #-fsanitize=address -fsanitize=leak
INC_PATH=-I./mlx_linux -I./inc -I./ -I./libft
LDFLAGS=-L./mlx_linux -lmlx -L./ -lXext -lX11 -lm -lz  -L./libft -lft

SRC_FILES=									\
	src/game/raycaster.c 					\
	src/game/ray_casting_logic.c			\
	src/game/render.c						\
	src/game/wall_detection.c				\
	src/game/sprite.c						\
	src/game/player.c						\
	src/utils/keyboard.c					\
	src/utils/map_utils.c	    			\
	src/utils/utils.c  						\
	src/utils/math_utils.c  				\
	src/utils/direction.c  					\
	src/utils/errors.c						\
	src/gnl/get_next_line_utils.c			\
	src/gnl/get_next_line.c					\
	src/parser/parser.c						\
	src/parser/utils_parser.c				\
	src/parser/texture_parser.c				\
	src/parser/map_parser.c					\
	

INC_FILES=									\
	inc/game/raycaster.h 					\
	inc/game/ray_casting_logic.h			\
	inc/game/render.h						\
	inc/game/wall_detection.h				\
	inc/game/sprite.h						\
	inc/game/player.h						\
	inc/utils/keyboard.h					\
	inc/utils/map_utils.h	    			\
	inc/utils/utils.h  						\
	inc/utils/math_utils.h  				\
	inc/utils/direction.h  					\
	inc/utils/errors.h						\
	inc/utils/defs.h						\
	inc/gnl/get_next_line.h					\
	inc/parser/parser.h						\
	inc/parser/utils_parser.h				\
	inc/parser/texture_parser.h				\
	inc/parser/map_parser.h					\

TEST_FILES= 								\
	test/main.c 							\
	test/test_horizontal_lines_detection.c 	\
	test/test_vertical_lines_detection.c 	\
	test/test_player_forward_move.c			\
	test/test_player_backward_move.c		\
	test/test_wall_distance.c				\
	test/test_intersection.c				\
	test/test_find_closest_wall.c			\
	test/test_find_sprite.c					\
	test/test_parser.c

all: libft $(NAME)

$(NAME): $(INC_FILES) $(SRC_FILES)
		@cp ./libft/libft.a .
		$(CC) $(CFLAGS) $(INC_PATH) $(SRC_FILES) src/main.c $(LDFLAGS) -o $(NAME)

test: $(INC_FILES) $(SRC_FILES) $(TEST_FILES)
	$(CC) -D GRID_SIZE=32 $(TEST_CFLAGS) $(INC_PATH) $(SRC_FILES) $(TEST_FILES) $(LDFLAGS) -o tester

clean:
	$(MAKE) clean -C ./libft
	rm -f $(SRC_OBJ)

re: fclean all


libft:
	$(MAKE) bonus -C ./libft

fclean: clean
	$(MAKE) fclean -C ./libft
	rm -f $(NAME)

.PHONY: all clean fclean re test libft
