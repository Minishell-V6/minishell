/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djeon <djeon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 19:52:35 by djeon             #+#    #+#             */
/*   Updated: 2021/06/16 17:13:39 by djeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				main(int argc, char *argv[], char *envp[])
{
	char		*line;
//	char		*path;
//	int			status;
//	pid_t		pid;
//	pid_t		wait_pid;
	t_cmd		*cmd_list;

//	argv[0] = "ls";
//	argv[1] = NULL;
	argc = 1;
	*argv = NULL;
	*envp = NULL;
	while ((line = readline("minishell $ ")) != NULL)
	{
//		path = NULL;
//		pid = -1;
		parse(&cmd_list, line);
//		if (ft_strncmp("ls", cmd_list->cmdline[0], 2) == 0)
//		{
//			pid = fork();
//			path = "/bin/ls";
//		}
		if (ft_strncmp("pwd", cmd_list->cmdline[0], 4) == 0)
			printf("%s\n", getcwd(NULL, 0));
		else if (ft_strncmp("exit", cmd_list->cmdline[0], 5) == 0)
			return (0);
		else
			ft_putstr_fd("command not found\n", 1);
//		if (path != NULL)
//		{
//			if (pid == 0)
//			{
//				execve(path, argv, envp);
//				path = NULL;
//				return (0);
//			}
//			else
//			{
//				while ((((wait_pid = wait(&status)) == -1) && errno == EINTR))
//				{
//				}
//			}
//		}
	}
	add_history(line);
	return (0);
}
