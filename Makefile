NAME = corewar
NAME2 = asm
CC = gcc
SRC = src
INCLUDE = include
LIBFT = libft
FlAGS = -Wall -Wextra -Werror
SRCS = corewar.c
SRCS2 = asm.c
OBJS = $(SRCS:.c=.o)
OBJS2 = $(SRCS2:.c=.o)

.PHONY: all re clean fclean

all: $(NAME) $(NAME2)

$(LIBFT)/libft.a:
	make -C $(LIBFT)

%.o: $(SRC)/%.c
	$(CC) $(FLAGS) -I $(INCLUDE) -I $(LIBFT) -o $@ -c $^

$(NAME): $(OBJS) $(LIBFT)/libft.a
	$(CC) $(FLAGS) -I $(INCLUDE) -I $(LIBFT) -o $(NAME) $(OBJS) -L $(LIBFT) -lft

$(NAME2): $(OBJS2) $(LIBFT)/libft.a
	$(CC) $(FLAGS) -I $(INCLUDE) -I $(LIBFT) -o $(NAME2) $(OBJS2) -L $(LIBFT) -lft

clean:
	rm -f $(OBJS)
	rm -f $(OBJS2)
	make -C $(LIBFT) clean

fclean: clean
	rm -f $(NAME)
	rm -f $(NAME2)
	make -C $(LIBFT) fclean

re: fclean all

norme:
	make -C $(LIBFT) norme
	norminette $(OBJS)
	norminette $(OBJS2)
