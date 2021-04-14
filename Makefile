NAME=raycaster
LIBFT=libft
MLX=mlx_linux
CC=clang
CFLAGS= -ggdb3 -Wall -Wextra -Werror -O3 #-fsanitize=address -fsanitize=leak
TEST_CFLAGS= -ggdb3 -Wall -Wextra -Werror #-fsanitize=address -fsanitize=leak
INC_PATH=-I./$(MLX) -I./ -I./$(LIBFT) -I./src
LDFLAGS=-L./$(MLX) -lmlx -L./ -lXext -lX11 -lm -lz  -L./$(LIBFT) -lft

SRC_FILES=									\
	src/render/render.c						\
	src/render/render_utils.c				\
	src/render/shade.c						\
	src/render/color.c						\
	src/game/game_utils.c 					\
	src/game/game.c 						\
	src/sprite/sprite.c						\
	src/sprite/sprite_render_utils.c		\
	src/sprite/sprite_render.c				\
	src/raycast/horizontal_detection.c		\
	src/raycast/vertical_detection.c		\
	src/walls/walls.c    					\
	src/raycast/raycast_utils.c 			\
	src/player/movement.c					\
	src/player/player.c						\
	src/game/keyboard.c						\
	src/utils/map_utils.c	    			\
	src/utils/math_utils.c  				\
	src/utils/angle_utils.c  				\
	src/utils/position.c	  				\
	src/utils/grid_position.c	  			\
	src/utils/direction.c  					\
	src/errors/errors.c						\
	src/parser/parser.c						\
	src/parser/parse_header.c				\
	src/parser/utils_parser.c				\
	src/parser/texture_parser.c				\
	src/parser/map_parser.c					\
	src/parser/map_parser_utils.c			\
	src/bmp/bmp.c

INC_FILES=									\
	src/utils/map_utils.h	    			\
	src/utils/math_utils.h  				\
	src/utils/angle_utils.c  				\
	src/utils/position.h	  				\
	src/utils/grid_position.h	  			\
	src/utils/direction.h  					\
	src/utils/defs.h						\
	src/render/color.h						\
	src/render/shade.h						\
	src/render/render.h						\
	src/render/render_utils.h				\
	src/walls/walls.h    					\
	src/raycast/raycast_utils.h 			\
	src/raycast/horizontal_detection.h 		\
	src/raycast/vertical_detection.h 		\
	src/game/keyboard.h						\
	src/errors/errors.h						\
	src/player/player.h						\
	src/player/movement.h					\
	src/game/game_utils.h 					\
	src/game/game.h 						\
	src/sprite/sprite.h						\
	src/sprite/sprite_render.h				\
	src/sprite/sprite_render_utils.h		\
	src/parser/parser.h						\
	src/parser/parse_header.h				\
	src/parser/utils_parser.h				\
	src/parser/texture_parser.h				\
	src/parser/map_parser.h					\
	src/parser/map_parser_utils.h			\
	src/bmp/bmp.h


TEST_FILES= 								\
	test/main.c 							\
	test/test_sprite.c						\
	test/test_parser.c						\
	test/test_horizontal_lines_detection.c 	\
	test/test_vertical_lines_detection.c 	\
	test/test_player_forward_move.c			\
	test/test_player_backward_move.c		\
	test/test_wall_distance.c				\
	test/test_intersection.c				\
	test/test_find_closest_wall.c			\
	

all: $(LIBFT) $(MLX) $(NAME)

$(NAME): $(INC_FILES) $(SRC_FILES)
		# @cp ./$(LIBFT)/$(LIBFT).a .
		$(CC) $(CFLAGS) $(INC_PATH) $(SRC_FILES) src/main.c $(LDFLAGS) -o $(NAME)

$(LIBFT):
	$(MAKE) -C ./$(LIBFT)

$(MLX):
	$(MAKE) -C ./$(MLX)

test: $(INC_FILES) $(SRC_FILES) $(TEST_FILES)
	$(CC) -D GRID_SIZE=32 $(TEST_CFLAGS) $(INC_PATH) $(SRC_FILES) $(TEST_FILES) $(LDFLAGS) -o tester

clean:
	$(MAKE) clean -C ./$(LIBFT)
	$(MAKE) clean -C ./$(MLX)

re: fclean all

fclean: clean
	$(MAKE) fclean -C ./$(LIBFT)
	$(MAKE) fclean -C ./$(MLX)
	rm -f $(LIBFT).a
	rm -f image.bmp

.PHONY: all clean fclean re test libft mlx_linux
