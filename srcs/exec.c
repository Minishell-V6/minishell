/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djeon <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 18:06:01 by djeon             #+#    #+#             */
/*   Updated: 2021/06/29 21:43:04 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int				non_builtin(t_cmd *cmd_list, char *argv[], char **envp, int fds[])
{
	char		*path;
	int			status;
	pid_t		pid;
	pid_t		wpid;

	path = NULL;
	if (ft_strncmp("ls", cmd_list->cmdline[0].cmd, 3) == 0)
		path = "/bin/ls";
	else if (ft_strncmp("ps", cmd_list->cmdline[0].cmd, 3) == 0)
		path = "/bin/ps";
	else if (ft_strncmp("cat", cmd_list->cmdline[0].cmd, 4) == 0)
		path = "/bin/cat";
	pid = fork();
	if (path != NULL && pid == 0)
	{
		if (cmd_list->pipe_flag == 1)
			dup2(fds[1], 1);
		argv[0] = "/bin/cat";
		argv[1] = cmd_list->cmdline[1];
		argv[2] = NULL;
		execve(path, argv, envp);
		exit(0);
	}
	else if (path != NULL && pid != 0)
	{
		wpid = waitpid(pid, &status, 0);
		dup2(100, STDOUT);
		dup2(101, STDIN);
		return (1);
	}
	else if (path == NULL && pid == 0)
		exit(0);
	cmd_list->err_manage->errcode = 1;
	return (0);
}

int				exec_function(t_cmd *cmd_list, char *argv[], char **envp[], int fds[])
{
	int fd;

//	if (redirect_check(cmd_list) == 1)
//		redirect(cmd_list);
	if (cmd_list->pipe_flag == 1)
		fd = fds[1];
	else
		fd = 1;
	if (ft_strncmp("pwd", cmd_list->cmdline[0].cmd, 4) == 0)
		return (ft_pwd(fd));
	else if (ft_strncmp("cd", cmd_list->cmdline[0].cmd, 3) == 0)
		return (ft_cd(cmd_list->cmdline[1].cmd));
	else if (ft_strncmp("exit", cmd_list->cmdline[0].cmd, 5) == 0)
		return (ft_exit(cmd_list));
	else if (ft_strncmp("env", cmd_list->cmdline[0].cmd, 4) == 0)
		ft_env(*envp, fd);
	else if (ft_strncmp("export", cmd_list->cmdline[0].cmd, 7) == 0)
		ft_export(cmd_list, envp, fd);
	else if (non_builtin(cmd_list, argv, *envp, fds) == 0)
		return (-1);
	dup2(100, STDOUT);
	dup2(101, STDIN);
	return (0);
}

void			exec(t_cmd *cmd_list, char *argv[], char **envp[])
{
	int			fds[2];
	int			status;
	pid_t		pid;
	pid_t		wpid;

	pipe(fds);
	if (exec_function(cmd_list, argv, envp, fds) == -1)
		print_errstr(cmd_list);
	if (cmd_list->pipe_flag == 1)
		pid = fork();
	else
		return ;
	if (pid == 0)
	{
		dup2(fds[0], 0);
		close(fds[0]);
		close(fds[1]);
		exec(cmd_list->next, argv, envp);
		exit(0);
	}
	else
	{
		close(fds[0]);
		wpid = waitpid(pid, &status, 0);
		return ;
	}
}
