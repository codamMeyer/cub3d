NAME=raycaster
CC=clang
CFLAGS= -ggdb3 -Wall -Wextra -Werror -fsanitize=address -fsanitize=leak
TEST_CFLAGS= -ggdb3 -Wall -Wextra -Werror #-fsanitize=address -fsanitize=leak
INC_PATH=-I./mlx_linux -I./ -I./libft -I./src
LDFLAGS=-L./mlx_linux -lmlx -L./ -lXext -lX11 -lm -lz  -L./libft -lft

SRC_FILES=									\
	src/render/render.c						\
	src/render/render_utils.c				\
	src/render/color.c						\
	src/game/game.c 						\
	src/sprite/sprite.c						\
	src/raycast/horizontal_detection.c		\
	src/raycast/vertical_detection.c		\
	src/walls/walls.c    					\
	src/raycast/raycast_utils.c 			\
	src/player/player.c						\
	src/game/keyboard.c						\
	src/utils/map_utils.c	    			\
	src/utils/math_utils.c  				\
	src/utils/angle_utils.c  				\
	src/utils/position.c	  				\
	src/utils/direction.c  					\
	src/errors/errors.c						\
	src/gnl/get_next_line_utils.c			\
	src/gnl/get_next_line.c					\
	src/parser/parser.c						\
	src/parser/utils_parser.c				\
	src/parser/texture_parser.c				\
	src/parser/map_parser.c					\
	src/bmp/bmp.c

INC_FILES=									\
	src/utils/map_utils.h	    			\
	src/utils/math_utils.h  				\
	src/utils/angle_utils.c  				\
	src/utils/position.h	  				\
	src/utils/direction.h  					\
	src/utils/defs.h						\
	src/render/color.h						\
	src/render/render.h						\
	src/render/render_utils.h				\
	src/walls/walls.h    					\
	src/raycast/raycast_utils.h 			\
	src/raycast/horizontal_detection.h 		\
	src/raycast/vertical_detection.h 		\
	src/game/keyboard.h						\
	src/errors/errors.h						\
	src/player/player.h						\
	src/game/game.h 						\
	src/sprite/sprite.h						\
	src/gnl/get_next_line.h					\
	src/parser/parser.h						\
	src/parser/utils_parser.h				\
	src/parser/texture_parser.h				\
	src/parser/map_parser.h					\
	src/bmp/bmp.h


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
