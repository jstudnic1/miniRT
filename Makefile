NAME = minirt

SRCS = 	main.c \
		src/parser/scene_parser.c \
       	src/parser/scene_parser_utils.c \
       	src/parser/scene_parser_objects.c \
       	src/render/vectors.c \
       	src/render/vectors_utils.c \
       	src/render/ray.c \
       	src/render/ray_utils.c \
       	src/render/color.c \
       	src/utils/ft_split.c \
       	src/utils/ft_atoi_atof.c \
       	src/utils/ft_calloc.c \
	   	src/render/intersect_plane.c \
       	src/utils/get_next_line.c

OBJS = $(SRCS:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror
MLX42 = ./MLX42/build/libmlx42.a
MLX42_BUILD_DIR = ./MLX42/build
CINCL = -Iinclude -ldl -lglfw -pthread -lm

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) $(MLX42) $(CINCL) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

mlx:
	git submodule init MLX42
	git submodule update MLX42
	cd MLX42; cmake -B build; make -C build -j4

mlx_clean:
	rm -rf $(MLX42_BUILD_DIR)

mlx_re: mlx_clean mlx

test: all
	./$(NAME)

.PHONY: all clean fclean re test 