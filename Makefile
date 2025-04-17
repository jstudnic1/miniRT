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
       	src/render/intersect_plane.c \
       	src/render/intersect_sphere.c \
       	src/render/intersect_cylinder.c \
       	src/render/render.c \
       	src/render/lighting.c \
       	src/utils/ft_split.c \
       	src/utils/ft_atoi_atof.c \
       	src/utils/ft_calloc.c \
       	src/utils/get_next_line.c \
		src/window/window_init.c \
		src/window/event_handlers.c \
		src/threads/deploy_threads.c

OBJS = $(SRCS:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror -g -Iinclude
MLX42 = ./MLX42/build/libmlx42.a
MLX42_BUILD_DIR = ./MLX42/build

# Define Linker Flags Separately
LDFLAGS = -L"/opt/homebrew/lib/" -lglfw -framework Cocoa -framework OpenGL -framework IOKit -ldl -pthread -lm

all: $(NAME)

# --- EXPLICIT COMPILATION RULES for problematic files ---
src/render/vectors.o: src/render/vectors.c incl/minirt.h
	@echo Compiling $@...
	$(CC) $(CFLAGS) -c $< -o $@

src/render/vectors_utils.o: src/render/vectors_utils.c incl/minirt.h
	@echo Compiling $@...
	$(CC) $(CFLAGS) -c $< -o $@

src/render/intersect_plane.o: src/render/intersect_plane.c incl/minirt.h
	@echo Compiling $@...
	$(CC) $(CFLAGS) -c $< -o $@

# --- GENERAL COMPILATION RULE (for others) ---
%.o: %.c incl/minirt.h
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(MLX42) $(LDFLAGS) -o $(NAME)

clean:
	rm -f $(OBJS) test_plane_runner

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

# --- TEST TARGETS ---

# Object files needed for plane intersection testing
TEST_PLANE_OBJS = src/render/intersect_plane.o src/render/vectors.o src/render/vectors_utils.o

# Generic .o rule above handles compilation

test_plane: $(TEST_PLANE_OBJS)
	@echo "Compiling and running plane intersection tests..."
	$(CC) tests/test_plane.c $(TEST_PLANE_OBJS) $(LDFLAGS) -o test_plane_runner
	./test_plane_runner

test: all
	./$(NAME)

.PHONY: all clean fclean re mlx mlx_clean mlx_re test test_plane $(TEST_PLANE_OBJS)
