/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djeon <djeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 18:06:01 by djeon             #+#    #+#             */
/*   Updated: 2021/07/01 21:08:16 by sejpark          ###   ########.fr       */
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
	if (stat(cmd_list->cmdline[0].cmd, buf) == 0)
	{
		non_builtin_exec(cmd_list, argv, envp, cmd_list->cmdline[0].cmd, fds);
		flag = 1;
	}
	else
	{
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
		i = -1;
		while (paths[++i] != NULL)
			free(paths[i]);
		free(paths);
	}
	free(buf);
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

	if (redirect_check(cmd_list) == 1) // redirect가 필요한 노드일 경우, redirect 함수를 실행합니다.
		redirect(cmd_list, &fds);
	if (cmd_list->pipe_flag == 1) // pipe_flag가 설정되어 list의 다음 노드가 존재할 경우, 현재 노드의 출력은 표준출력이 아닌 다음 노드로 넘겨줘야 하므로 fd에 파이프의 입력fd를 넣어줍니다. 그렇지 않을경우, 표준출력 fd인 1을 fd에 넣어줍니다.
		fd = fds[1];
	else
		fd = 1;
	if (ft_strncmp("pwd", cmd_list->cmdline[0].cmd, 4) == 0) // 명령어는 커맨드라인의 처음부분에만 올 수 있으므로 cmdline의 첫번째 index를 과제에서 구현해야하는 명령어와 비교하여 일치할 시, 조건문의 함수를 실행합니다.
		return (ft_pwd(fd));
	else if (ft_strncmp("cd", cmd_list->cmdline[0].cmd, 3) == 0)
		return (ft_cd(cmd_list));
	else if (ft_strncmp("exit", cmd_list->cmdline[0].cmd, 5) == 0)
		return (ft_exit(cmd_list));
	else if (ft_strncmp("env", cmd_list->cmdline[0].cmd, 4) == 0)
		ft_env(*envp, fd);
	else if (ft_strncmp("export", cmd_list->cmdline[0].cmd, 7) == 0)
		ft_export(cmd_list, envp, fd);
	else if (ft_strncmp("unset", cmd_list->cmdline[0].cmd, 6) == 0)
		ft_unset(cmd_list, *envp);
	else if (non_builtin(cmd_list, argv, *envp, fds) == 0) // 위의 해당하는 명령어가 아닐경우, non_built 함수에서 입력된 명령어가 유효한 명령어인지 최종적으로 확인합니다. 유효한 명령어일 경우, 내장된 프로그램이 실행되고 아닐경우, 오류가 출력됩니다.
		return (-1);
	return (0);
}

void			exec(t_cmd *cmd_list, char *argv[], char **envp[])
{
	int			fds[2];
	int			status;
	pid_t		pid;
	pid_t		wpid;

	pipe(fds); // 부모프로세스와 자식프로세스간 통신을 위해 pipe를 생성합니다. 크기가 2인 fds배열엔 생성된 pipe의 입출력 fd가 들어갑니다.(입력 : fds[1] == 4, 출력 : fds[0] == 3)
	if (exec_function(cmd_list, argv, envp, fds) == -1) // 명령어에 맞게 프로그램을 실행합니다.
		print_errstr(cmd_list); // 프로그램 실행 도중 오류 발생 시, 오류 메시지를 출력합니다.
	dup2(100, STDOUT); // redirection 기능이 동작하면 입출력 fd는 입출력 기능이 아닌 다른 file을 가리키게 됩니다. 그래서 main에서 backup해뒀던 표준입출력을 가리키는 fd인 100, 101을 이용하여 표준입출력 fd의 기능을 원상복구 시킵니다.
	dup2(101, STDIN);
	if (cmd_list->pipe_flag == 1) // 파이프 처리가 필요할 경우, 자식프로세스를 생성합니다. 파이프 처리가 필요하지 않을경우, 현재 함수를 종료합니다.
		pid = fork();
	else
		return ;
	if (pid == 0) // pid로 0을 반환받는 자식프로세스가 실행되는 조건문입니다.
	{
		dup2(fds[0], 0); // 자식프로세스에서 부모프로세스의 표준출력을 받아야하기 때문에 자식프로세스의 표준입력 fd가 부모프로세스의 표준출력을 받는 파이프의 출력 fd인 fds[0]을 가리키게 합니다.
		close(fds[0]); // 사용하지 않는 fd는 닫아줍니다.
		close(fds[1]);
		exec(cmd_list->next, argv, envp); // 자식프로세스로 실행될 명령어가 동작할 수 있게끔 현재함수를 재귀로 실행시켜줍니다.
		exit(0); // 명령어의 동작이 끝나면 자식프로세스를 종료시킵니다.
	}
	else // pid로 자식프로세스의 주소를 반환받는 부모프로세스가 실행되는 조건문입니다.
	{
		close(fds[0]);
		wpid = waitpid(pid, &status, 0); // 부모프로세스는 자식프로세스가 종료될때까지 waitpid함수에서 대기하고, 자식프로세스가 종료되어 status에 자식프로세스의 종료상태가 입력되면 waitpid함수는 반환됩니다. 
		return ;
	}
}
