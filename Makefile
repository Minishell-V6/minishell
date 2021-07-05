# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: seuyu <seuyu@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/25 19:30:48 by djeon             #+#    #+#              #
#    Updated: 2021/07/05 13:02:24 by sejpark          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC 				= gcc
#CC 				= gcc -g -fsanitize=address
RM				= rm -rf
CFLAGS 			= -Wall -Wextra -Werror
NAME 			= minishell

#READLINE_LIB 	= -lreadline -L/usr/local/opt/readline/lib
#READLINE_INC	= -I/usr/local/opt/readline/include

READLINE_LIB 	= -lreadline -L /Users/$(USER)/.brew/opt/readline/lib
READLINE_INC	= -I /Users/$(USER)/.brew/opt/readline/include

READLINE_LIB	= -lreadline -L/opt/homebrew/opt/readline/lib
READLINE_INC	= -I/opt/homebrew/opt/readline/include

LIBFT		= libft.a
LIBFT_DIR	= libft

SRC_DIR 	= srcs
SRC 		= srcs/minishell.c srcs/utils.c srcs/parse.c srcs/exec.c \
	  	  	  srcs/error_management.c srcs/ft_cd.c srcs/ft_exit.c \
			  srcs/ft_env.c srcs/ft_pwd.c srcs/ft_export.c srcs/export_utils.c \
			  srcs/signal_handle.c srcs/alloc_token.c srcs/cmd_split.c \
			  srcs/get_parse_size.c srcs/redir_chk.c srcs/ft_getenv.c \
			  srcs/redirect.c srcs/redirect_check.c \
			  srcs/ft_echo.c srcs/unset.c

OBJ_DIR 	= objs
OBJ 		= $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all : 		$(NAME)

$(NAME) : 	$(LIBFT) $(OBJ)
			$(CC) $(CFLAGS) -o $@ $(OBJ) $(READLINE_LIB) $(READLINE_INC) \
			$(LIBFT)

$(LIBFT) :
			cd $(LIBFT_DIR); make
			cp $(LIBFT_DIR)/$(LIBFT) ./

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
			mkdir -p $(OBJ_DIR)
			$(CC) $(CFLAGS) -c $< -o $(<:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o) \
			$(READLINE_INC)

clean :
			cd $(LIBFT_DIR); make clean
			$(RM) $(OBJ) $(OBJ_DIR)

fclean : 	clean
			cd $(LIBFT_DIR); make fclean
			$(RM) $(NAME) $(LIBFT)

re : 		fclean all

.PHONY :	all clean fclean
