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
CFLAGS = -Wall -Wextra -Werror -I../lib
LDFLAGS = -lm

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

test: all
	./$(NAME)

.PHONY: all clean fclean re test 