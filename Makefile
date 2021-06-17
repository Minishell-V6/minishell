# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: djeon <djeon@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/25 19:30:48 by djeon             #+#    #+#              #
#    Updated: 2021/06/17 16:58:44 by djeon            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
HEADER = minishell.h
CFLAGS = -Wall -Wextra -Werror
NAME = minishell
SRC = minishell.c utils.c parse.c exec.c error_management.c \
		ft_cd.c ft_exit.c \
	  ./get_next_line/get_next_line.c ./get_next_line/get_next_line_utils.c
OBJECTS = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBJECTS)
	make all -C libft/
	$(CC) $(CFLAGS) -o $@ $(OBJECTS) -lreadline libft/libft.a

clean :
	rm -f $(OBJECTS)
	make clean -C libft/

fclean : clean
	rm -f $(NAME)
	make fclean -C libft/

re : fclean all
