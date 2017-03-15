NAME = libft.a
CC = gcc
INCLUDES = include
SRC = src
LIB = ..
FLAGS = -Wall -Wextra -Werror
SRCS = ft_printf.c\
	   if_forest.c\
	   number.c\
	   unsigned.c\
	   string.c\
	   char.c\
	   params.c\
	   pointer.c\
	   long.c\
	   other.c
OBJS = $(SRCS:.c=.o)

.PHONY: clean fclean all re norme $(NAME)

all: $(NAME)

$(NAME): $(OBJS)
	@echo "\033[0m\033[44m\033[37m\033[1m[ft_printf]\033[40m\033[1m making ft_printf"
	@cp $(LIB)/$(NAME) $(NAME)
	@ar rc $(NAME) $(OBJS)
	@ranlib $(NAME)
	@echo "\033[0m\033[44m\033[37m\033[1m[ft_printf]\033[40m\033[1m done\033[0m"

%.o: $(SRC)/%.c
	@echo "\033[0m\033[46m\033[37m\033[1m[ft_printf]\033[0m\033[40m\033[33m making '$@'"
	@$(CC) $(FLAGS) -I $(INCLUDES) -I $(LIB) -o $@ -c $^

clean:
	@echo "\033[0m\033[44m\033[37m\033[1m[ft_printf]\033[0m\033[40m\033[36m cleaning objects"
	@rm -f $(OBJS)
	@echo "\033[0m\033[44m\033[37m\033[1m[ft_printf]\033[0m\033[40m\033[36m done\033[0m"

fclean: clean
	@echo "\033[0m\033[44m\033[37m\033[1m[ft_printf]\033[0m\033[40m\033[34m cleaning archive"
	@rm -f $(NAME)
	@echo "\033[0m\033[44m\033[37m\033[1m[ft_printf]\033[0m\033[40m\033[34m done\033[0m"

norme:
	@echo "\033[0m\033[44m\033[37m\033[1m[ft_printf]\033[40m\033[1m making norme\033[32m"
	@norminette $(SRC) $(INCLUDES)
	@echo "\033[0m\033[44m\033[1m[ft_printf]\033[40m\033[1m done\033[32m"

re: fclean all
