/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djeon <djeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 18:06:01 by djeon             #+#    #+#             */
/*   Updated: 2021/06/30 22:00:38 by djeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void			non_builtin_exec(t_cmd *cmd_list, char *argv[], char **envp, char *path, int fds[])
{
	int			status;
	pid_t		pid;
	pid_t		wpid;
	int			i;

	i = 1;
	argv[0] = path;
	while (cmd_list->cmdline[i].cmd != NULL && cmd_list->cmdline[i].redir_flag == 0)
	{
		argv[i] = cmd_list->cmdline[i].cmd;
		i++;
	}
	argv[i] = NULL;
	pid = fork();
	if (pid == 0)
	{
		if (cmd_list->pipe_flag == 1)
			dup2(fds[1], 1);
		execve(path, argv, envp);
		exit(0);
	}
	else if (pid != 0)
		wpid = waitpid(pid, &status, 0);
	dup2(100, STDOUT);
	dup2(101, STDIN);
}

int				non_builtin(t_cmd *cmd_list, char *argv[], char **envp, int fds[])
{
	struct stat	*buf;
	char		*env_path;
	char		**paths;
	char		*tmp;
	int			i;
	int			flag;

	i = -1;
	flag = 0;
	if (!(buf = (struct stat*)malloc(sizeof(struct stat))))
		return (-1);
	if ((env_path = get_env_value("PATH", envp)) == NULL)
		return (-1);
	paths = ft_split(env_path, ':');
	while (paths[++i] != NULL)
	{
		tmp = strjoin_path(paths[i], cmd_list->cmdline[0].cmd);
		if (stat(tmp, buf) == 0)
		{
			non_builtin_exec(cmd_list, argv, envp, tmp, fds);
			flag = 1;
			free(tmp);
			break ;
		}
		free(tmp);
	}
//	free(env_path);
//	i = -1;
//	while (paths[++i] != NULL)
//		free(paths[i]);
//	free(paths);
	if (flag == 0)
	{
		cmd_list->err_manage->errcode = 1;
		return (0);
	}
	return (1);
}

int				exec_function(t_cmd *cmd_list, char *argv[], char **envp[], int fds[])
{
	int fd;

	if (redirect_check(cmd_list) == 1)
		redirect(cmd_list, &fds);
	if (cmd_list->pipe_flag == 1)
		fd = fds[1];
	else
		fd = 1;
	if (ft_strncmp("pwd", cmd_list->cmdline[0].cmd, 4) == 0)
		return (ft_pwd(fd));
	else if (ft_strncmp("cd", cmd_list->cmdline[0].cmd, 3) == 0)
		return (ft_cd(cmd_list));
	else if (ft_strncmp("exit", cmd_list->cmdline[0].cmd, 5) == 0)
		return (ft_exit(cmd_list));
	else if (ft_strncmp("env", cmd_list->cmdline[0].cmd, 4) == 0)
		ft_env(*envp, fd);
	else if (ft_strncmp("export", cmd_list->cmdline[0].cmd, 7) == 0)
		ft_export(cmd_list, envp, fd);
	else if (non_builtin(cmd_list, argv, *envp, fds) == 0)
		return (-1);
 // 이거 여기만 있으니까 위에 리턴으로 빠져버리면 적용이 안되네요.
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
	{
		print_errstr(cmd_list);
	}
	dup2(100, STDOUT);
	dup2(101, STDIN);
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
