NAME = libft.a
CC = gcc
LIBFT = libft
PRINTF = ft_printf
JOINF = ft_joinf
FLAGS = -Wall -Wextra -Werror

.PHONY: clean fclean all re norme $(NAME) $(LIBFT) $(PRINTF) $(JOINF)

all: $(NAME)

$(LIBFT):
	@echo "\033[0m\033[44m\033[37m\033[1m[libft]\033[40m\033[1m making original libft"
	@make -C $(LIBFT)
	@cp $(LIBFT)/$(NAME) $(NAME)
	@echo "\033[0m\033[44m\033[37m\033[1m[libft]\033[40m\033[1m done\033[0m"

$(PRINTF):
	@echo "\033[0m\033[44m\033[37m\033[1m[libft]\033[40m\033[1m making ft_printf"
	@make -C $(PRINTF)
	@cp $(PRINTF)/$(NAME) $(NAME)
	@echo "\033[0m\033[44m\033[37m\033[1m[libft]\033[40m\033[1m done\033[0m"

$(JOINF):
	@echo "\033[0m\033[44m\033[37m\033[1m[libft]\033[40m\033[1m making ft_joinf"
	@make -C $(JOINF)
	@cp $(JOINF)/$(NAME) $(NAME)
	@echo "\033[0m\033[44m\033[37m\033[1m[libft]\033[40m\033[1m done\033[0m"

$(NAME): $(LIBFT) $(JOINF) $(PRINTF)
	@ranlib $(NAME)

%.o: %.c
	@echo "\033[0m\033[46m\033[37m\033[1m[libft]\033[0m\033[40m\033[33m making '$@'"
	@$(CC) $(FLAGS) -I $(INCLUDES) -o $@ -c $^

clean:
	@echo "\033[0m\033[44m\033[37m\033[1m[libft]\033[0m\033[40m\033[36m cleaning sub-directories"
	@make -C $(LIBFT) clean
	@make -C $(PRINTF) clean
	@make -C $(JOINF) clean
	@echo "\033[0m\033[44m\033[37m\033[1m[libft]\033[0m\033[40m\033[36m done\033[0m"

fclean: clean
	@echo "\033[0m\033[44m\033[37m\033[1m[libft]\033[0m\033[40m\033[34m cleaning sub-directories"
	@make -C $(LIBFT) fclean
	@make -C $(PRINTF) fclean
	@make -C $(JOINF) fclean
	@echo "\033[0m\033[44m\033[37m\033[1m[libft]\033[0m\033[40m\033[34m done\033[0m"
	@echo "\033[0m\033[44m\033[37m\033[1m[libft]\033[0m\033[40m\033[34m cleaning archive"
	@rm -f $(NAME)
	@echo "\033[0m\033[44m\033[37m\033[1m[libft]\033[0m\033[40m\033[34m done\033[0m"

norme:
	@echo "\033[0m\033[44m\033[37m\033[1m[libft]\033[40m\033[1m making norme\033[32m"
	@make -C $(LIBFT) norme
	@make -C $(PRINTF) norme
	@make -C $(JOINF) norme
	@echo "\033[0m\033[44m\033[1m[libft]\033[40m\033[1m done\033[32m"

re: fclean all