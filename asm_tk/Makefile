# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tdouge <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/03/07 01:33:37 by tdouge            #+#    #+#              #
#    Updated: 2017/03/07 01:33:40 by tdouge           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME	= test

SRC		=	get_next_line.c test.c check_type.c

OBJ		= $(addprefix src/,$(SRC:.c=.o))

CFLAGS	=  -Iincludes/ -Ilibft/includes/

$(NAME): $(OBJ)
	make -C libft
	gcc -Werror -Wextra -Wall $(OBJ) -o $(NAME) -L libft/ -lft -Ilibft/includes/

all: $(NAME)

clean:
	make -C libft/ clean
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME) $(OBJ)
	make -C libft/ fclean
	
re: fclean $(NAME)