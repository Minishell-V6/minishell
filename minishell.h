/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojeong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 19:54:23 by djeon             #+#    #+#             */
/*   Updated: 2021/06/19 11:36:03 by mac              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include <stdio.h>


# define STDIN 			0
# define STDOUT 		1
# define STDERR 		2

typedef struct	s_err
{
	int				errcode;
	int				errindex;
}				t_err;

typedef struct	s_cmd
{
	char			**cmdline;
	int				pipe_flag;
	char			quote;
	struct s_err	*err_manage;
	struct s_cmd	*next;
}				t_cmd;

void				parse(t_cmd **cmd_list, char *line);
t_cmd				*ft_new(char *line, int pipe_flag, char quote);
char				check_quote(char *line);
int					exec(t_cmd *cmd_list, char *argv[], char **envp[]);
int					ft_cd(char *string);
int					ft_exit(t_cmd *cmd_list);
void				print_errstr(t_cmd *cmd_list);
void				free_all(t_cmd *cmd_list);

// env
void				ft_env(char **envp);
char				**copy_envp(char **envs);
//export
void				print_export(char **envp);
int					isvalid_export(char *line);
void				remove_char(char *str, char c);
int					cnt_envp_row(char **envp);
void				ft_export(t_cmd *cmd_list, char ***envp);
int					add_envp(t_cmd *cmd_list, char ***envp);
char				**sort_env(char **envp);
void				print_quote(char *str);
int					check_key(char **envp, char *line);
int					haveequal(char *line);
#endif
