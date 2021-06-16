/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djeon <djeon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 19:54:23 by djeon             #+#    #+#             */
/*   Updated: 2021/06/16 18:10:18 by djeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./get_next_line/get_next_line.h"
# include "./libft/libft.h"
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>




# include <stdio.h>

typedef struct	s_cmd
{
	char			**cmdline;
	int				pipe_flag;
	char			quote;
	struct s_cmd	*next;
}				t_cmd;

void				parse(t_cmd **cmd_list, char *line);
t_cmd				*ft_new(char *line, int pipe_flag, char quote);
char				check_quote(char *line);
void				exec(t_cmd *cmd_list, char *argv[], char *envp[]);
void				ft_cd(char *string);

#endif
