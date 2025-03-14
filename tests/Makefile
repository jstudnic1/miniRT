NAME = test_parser

SRCS = test_parser.c \
       ../srcs/scene_parser.c \
       ../srcs/scene_parser_utils.c \
       ../srcs/scene_parser_objects.c \
       ../srcs/vectors.c \
       ../srcs/vectors_utils.c \
       ../srcs/ray.c \
       ../srcs/ray_utils.c \
       ../srcs/color.c \
       ../srcs/ft_split.c \
       ../srcs/ft_atoi_atof.c \
       ../srcs/ft_calloc.c \
       ../srcs/get_next_line.c

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