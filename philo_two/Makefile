# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: memilio <memilio@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/25 15:21:21 by memilio           #+#    #+#              #
#    Updated: 2020/11/02 13:20:34 by memilio          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	philo_two
CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror -g
INCLUDES	=	-I./includes/
FOLDER_SRCS	=	./srcs/
FUNC		=	philo_two \
				parse \
				utils \
				simulation \
				simulation_utils
SRC			=	$(addprefix $(FOLDER_SRCS), $(FUNC))
OBJ			=	$(SRC:=.o)

.PHONY: all clean fclean re norme

all: $(NAME)
	@echo "\033[32m[+] Make completed\033[0m"

$(NAME): $(OBJ)
	@$(CC) $(OBJ) $(INCLUDES) -o $(NAME)

$(OBJ): %.o: %.c
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

norme:
	@norminette ./includes
	@norminette ./srcs