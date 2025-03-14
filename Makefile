NAME = minirt

SRCS = 	main.c \
		src/scene_parser.c \
       	src/scene_parser_utils.c \
       	src/scene_parser_objects.c \
       	src/vectors.c \
       	src/vectors_utils.c \
       	src/ray.c \
       	src/ray_utils.c \
       	src/color.c \
       	src/ft_split.c \
       	src/ft_atoi_atof.c \
       	src/ft_calloc.c \
	   	src/intersect_plane.c \
       	src/get_next_line.c

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