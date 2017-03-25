NAME = corewar
NAME2 = asm
CC = gcc
SRC = src
INCLUDE = include
LIBFT = libft
LIBS = lib
FLAGS = -Wall -Wextra -Werror
ENDFLAGS = -framework Appkit -framework OpenGL
SRCS = corewar.c\
	   error.c\
	   flags.c\
	   champions.c\
	   process.c\
	   vm.c\
	   execution.c\
	   window.c\
	   op.c\
	   actions_1.c\
	   actions_2.c\
	   actions_3.c\
	   actions_4.c\
	   machine_action.c\
	   draw.c\
	   draw_2.c
SRCS2 = asm.c\
		error.c
OBJS = $(SRCS:.c=.o)
OBJS2 = $(SRCS2:.c=.o)

.PHONY: all re clean fclean

all: $(NAME) $(NAME2)

$(LIBFT)/libft.a:
	make -C $(LIBFT)

%.o: $(SRC)/%.c
	$(CC) $(FLAGS) -I $(INCLUDE) -I $(LIBFT) -I $(LIBS)/include -o $@ -c $^

$(INCLUDE)/corewar.h: $(OBJS)

$(INCLUDE)/asm.h: $(OBJS2)

$(NAME): $(LIBFT)/libft.a $(INCLUDE)/corewar.h $(OBJS)
	$(CC) $(FLAGS) -I $(INCLUDE) -I $(LIBFT) -I $(LIBS)/include -o $(NAME) $(OBJS) -L $(LIBFT) -lft -L $(LIBS) -lSDL2 -lSDL2main -lSDL2_ttf $(ENDFLAGS)

$(NAME2): $(LIBFT)/libft.a $(INCLUDE)/asm.h $(OBJS2)
	$(CC) $(FLAGS) -I $(INCLUDE) -I $(SDL)/include -I $(LIBFT) -o $(NAME2) $(OBJS2) -L $(LIBFT) -lft

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
