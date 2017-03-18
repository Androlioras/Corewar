NAME = corewar
NAME2 = asm
CC = gcc
SRC = src
INCLUDE = include
LIBFT = libft
FLAGS = -Wall -Wextra -Werror -Wno-deprecated-declarations
ENDFLAGS = -framework GLUT -framework OpenGL
SRCS = corewar.c\
	   error.c\
	   flags.c\
	   champions.c\
	   process.c\
	   vm.c\
	   execution.c\
	   window.c\
	   op.c
SRCS2 = asm.c\
		error.c
OBJS = $(SRCS:.c=.o)
OBJS2 = $(SRCS2:.c=.o)

.PHONY: all re clean fclean

all: $(NAME) $(NAME2)

$(LIBFT)/libft.a:
	make -C $(LIBFT)

%.o: $(SRC)/%.c
	$(CC) $(FLAGS) -I $(INCLUDE) -I $(LIBFT) -o $@ -c $^

$(INCLUDE)/corewar.h: $(OBJS)

$(INCLUDE)/asm.h: $(OBJS2)

$(NAME): $(LIBFT)/libft.a $(INCLUDE)/corewar.h $(OBJS)
	$(CC) $(FLAGS) -I $(INCLUDE) -I $(LIBFT) -o $(NAME) $(OBJS) -L $(LIBFT) -lft $(ENDFLAGS)

$(NAME2): $(LIBFT)/libft.a $(INCLUDE)/asm.h $(OBJS2)
	$(CC) $(FLAGS) -I $(INCLUDE) -I $(LIBFT) -o $(NAME2) $(OBJS2) -L $(LIBFT) -lft

clean:
	rm -f $(OBJS)
	rm -f $(OBJS2)
	@make -C $(LIBFT) clean

fclean: clean
	rm -f $(NAME)
	rm -f $(NAME2)
	@make -C $(LIBFT) fclean

re: fclean all

norme:
	@make -C $(LIBFT) norme
	@norminette $(SRC) $(INCLUDE)
