# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: seojeong <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/25 19:30:48 by djeon             #+#    #+#              #
#    Updated: 2021/06/22 12:21:19 by sejpark          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC 			= gcc
RM			= rm -rf
#HEADER 	= minishell.h
CFLAGS 		= -Wall -Wextra -Werror
NAME 		= minishell

LIBFT		= libft.a
LIBFT_DIR	= libft

SRC_DIR 	= srcs
SRC 		= srcs/minishell.c srcs/utils.c srcs/parse.c srcs/exec.c \
	  	  	  srcs/error_management.c srcs/ft_cd.c srcs/ft_exit.c srcs/ft_env.c\
			  srcs/ft_export.c srcs/export_utils.c

OBJ_DIR 	= objs
OBJ 		= $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all : 		$(NAME)

$(NAME) : 	$(LIBFT) $(OBJ)
			$(CC) $(CFLAGS) -o $@ $(OBJ) -lreadline $(LIBFT)

$(LIBFT) :
			cd $(LIBFT_DIR); make
			cp $(LIBFT_DIR)/$(LIBFT) ./

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
			mkdir -p $(OBJ_DIR)
			$(CC) $(CFLAGS) -c $< -o $(<:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

clean :
			cd $(LIBFT_DIR); make clean
			$(RM) $(OBJ) $(OBJ_DIR)

fclean : 	clean
			cd $(LIBFT_DIR); make fclean
			$(RM) $(NAME) $(LIBFT)

re : 		fclean all

.PHONY :	all clean fclean
