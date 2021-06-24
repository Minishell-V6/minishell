/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojeong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 19:54:23 by djeon             #+#    #+#             */
/*   Updated: 2021/06/23 16:21:32 by djeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
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
int					exec_function(t_cmd *cmd_list, char *argv[], char **envp[], int fds[]);
int					exec(t_cmd *cmp_list, char *argv[], char **envp[]);
int					ft_cd(char *string);
int					ft_exit(t_cmd *cmd_list);
void				print_errstr(t_cmd *cmd_list);
void				free_all(t_cmd *cmd_list);

// env
void				ft_env(char **envp);
char				**copy_envp(char **envs);
//export
void				ft_export(t_cmd *cmd_list, char ***envp);
int					add_envp(t_cmd *cmd_list, char ***envp);
int					isvalid_export(char *line);
int					cnt_envp_row(char **envp);
char				**sort_env(char **envp);
int					haveequal(char *line);
void				add_key_envp(char ***envp, t_cmd *cmd_list, int keyindex);
#endif
