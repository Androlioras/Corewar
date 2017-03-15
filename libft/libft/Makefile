NAME = libft.a
SRCS = ft_alloc_array.c\
	   ft_arraylen.c\
	   ft_atoi.c\
	   ft_bzero.c\
	   ft_factorial.c\
	   ft_free_array.c\
	   ft_get_next_line.c\
	   ft_isalnum.c\
	   ft_isalpha.c\
	   ft_isascii.c\
	   ft_isdigit.c\
	   ft_isprime.c\
	   ft_isprint.c\
	   ft_itoa.c\
	   ft_lstadd.c\
	   ft_lstdel.c\
	   ft_lstdelone.c\
	   ft_lstiter.c\
	   ft_lstmap.c\
	   ft_lstnew.c\
	   ft_lstswap.c\
	   ft_memalloc.c\
	   ft_memccpy.c\
	   ft_memchr.c\
	   ft_memcmp.c\
	   ft_memcpy.c\
	   ft_memdel.c\
	   ft_memmove.c\
	   ft_memset.c\
	   ft_power.c\
	   ft_putchar.c\
	   ft_putchar_fd.c\
	   ft_putendl.c\
	   ft_putendl_fd.c\
	   ft_putnbr.c\
	   ft_putnbr_fd.c\
	   ft_putstr.c\
	   ft_putstr_fd.c\
	   ft_showtab.c\
	   ft_showtab_fd.c\
	   ft_sqrt.c\
	   ft_strcat.c\
	   ft_strchr.c\
	   ft_strclr.c\
	   ft_strcmp.c\
	   ft_strcpy.c\
	   ft_strdel.c\
	   ft_strdup.c\
	   ft_strequ.c\
	   ft_striter.c\
	   ft_striteri.c\
	   ft_strjoin.c\
	   ft_strlcat.c\
	   ft_strlen.c\
	   ft_strmap.c\
	   ft_strmapi.c\
	   ft_strncat.c\
	   ft_strncmp.c\
	   ft_strncpy.c\
	   ft_strndup.c\
	   ft_strnequ.c\
	   ft_strnew.c\
	   ft_strnstr.c\
	   ft_strrchr.c\
	   ft_strsplit.c\
	   ft_strstr.c\
	   ft_strsub.c\
	   ft_strtrim.c\
	   ft_tolower.c\
	   ft_toupper.c
OBJS = $(SRCS:.c=.o)
FLAGS = -Wall -Wextra -Werror
INCLUDES = include
SRC = src

.PHONY: clean fclean all re norme $(NAME)

all: $(NAME)

%.o: $(SRC)/%.c
	@echo "\033[0m\033[46m\033[37m\033[1m[libft original]\033[0m\033[40m\033[33m making '$@'"
	@$(CC) $(FLAGS) -I $(INCLUDES) -o $@ -c $^

$(NAME): $(OBJS)
	@echo "\033[0m\033[46m\033[37m\033[1m[libft original]\033[40m\033[1m\033[37m making libft"
	@ar rc $(NAME) $(OBJS)
	@ranlib $(NAME)
	@echo "\033[0m\033[46m\033[37m\033[1m[libft original]\033[40m\033[1m\033[37m done"

clean:
	@echo "\033[0m\033[46m\033[37m\033[1m[libft original]\033[0m\033[40m\033[36m cleaning objects"
	@rm -f $(OBJS)
	@echo "\033[0m\033[46m\033[37m\033[1m[libft original]\033[0m\033[40m\033[36m done"

fclean: clean
	@echo "\033[0m\033[46m\033[37m\033[1m[libft original]\033[0m\033[40m\033[34m cleaning archive"
	@rm -f $(NAME)
	@echo "\033[0m\033[46m\033[37m\033[1m[libft original]\033[0m\033[40m\033[34m done"

norme:
	@echo "\033[0m\033[46m\033[37m\033[1m[libft original]\033[0m\033[40m\033[1m making norme\033[32m"
	@norminette $(SRC) $(INCLUDES)
	@echo "\033[0m\033[46m\033[37m\033[1m[libft original]\033[0m\033[40m\033[1m done\033[32m"

re: fclean all
