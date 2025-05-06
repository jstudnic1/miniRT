NAME = minirt

SRCS = 	main.c \
		src/parser/scene_parser.c \
       	src/parser/scene_parser_utils.c \
       	src/parser/scene_parser_objects.c \
       	src/render/vectors.c \
       	src/render/vectors_utils.c \
       	src/render/ray.c \
       	src/render/color.c \
       	src/render/intersect_plane.c \
       	src/render/intersect_sphere.c \
       	src/render/intersect_cylinder.c \
       	src/render/render_utils.c \
       	src/render/render.c \
       	src/render/lighting.c \
       	src/utils/ft_split.c \
       	src/utils/ft_atoi_atof.c \
       	src/utils/ft_calloc.c \
       	src/utils/get_next_line.c \
		src/window/window_init.c \
		src/window/event_handlers.c \
		src/threads/deploy_threads.c \
		src/utils/time.c \
		src/debug/scene_print.c \
		src/utils/ft_realloc.c \
		src/parser/scene_parser_save_data.c \
		src/utils/ft_strdup_join_chr.c \
		src/parser/parse_values.c \
		src/render/vector_utils_1.c

OBJS = $(SRCS:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
MLX42 = ./MLX42/build/libmlx42.a
MLX42_BUILD_DIR = ./MLX42/build
CINCL = -Iinclude -L/opt/homebrew/lib -ldl -lglfw -pthread -lm -gdwarf-4 -fsanitize=address -static-libsan

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
