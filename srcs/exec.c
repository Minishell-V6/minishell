/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seuyu <seuyu@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 18:06:01 by djeon             #+#    #+#             */
/*   Updated: 2021/07/04 19:31:53 by mac              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int				non_builtin_exec(t_cmd *cmd_list, char *argv[], char **envp, char *path, int fds[])
{
	int			status;
	pid_t		pid;
	pid_t		wpid;
	int			i;

	i = 1;
	argv[0] = path; // path는 입력된 명령어에 해당하는 프로그램의 경로입니다.
	while (cmd_list->cmdline[i].cmd != NULL && cmd_list->cmdline[i].redir_flag == 0) // 인자가 필요한 프로그램의 경우, 인자를 활용해야하므로 argv에 인자 넣는 작업을 거칩니다. while loop의 조건은 cmd가 존재하거나 redirection 기호가 아닐때까지 입니다.
	{
		argv[i] = cmd_list->cmdline[i].cmd;
		i++;
	}
	argv[i] = NULL;
	if ((pid = fork()) < -1) // 자식프로세스를 생성합니다.
		return (-1);
	if (pid == 0) // 자식프로세스가 실행하는 부분입니다.
	{
		if (cmd_list->pipe_flag == 1) // 현재 명령어 뒤에 실행할 명령어가 존재할 경우, 표준출력이 아닌 다음 명령어에 보내주기 위해 dup2함수를 실행합니다.
			dup2(fds[1], 1);
		if (execve(path, argv, envp) == -1) // 자식프로세스는 path에 해당하는 프로그램을 실행시킨 후에 프로세스를 종료시킵니다.
			return (-1);
	}
	else if (pid != 0) // 부모프로세스가 실행하는 부분입니다.
	{
		wpid = waitpid(pid, &status, 0);
		g_exit_status = status >> 8;
	}
	return (0);
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
	if (!(buf = (struct stat*)malloc(sizeof(struct stat)))) // stat함수에 쓸 매개변수에 메모리 할당
	{
		free(buf);
		return (0);
	}
	if (cmd_list->cmdline[0].cmd[0] != '\0' && stat(cmd_list->cmdline[0].cmd, buf) == 0) // 프롬프트에 입력된 명령어가 상대경로나 절대경로가 포함된 명령어일 경우, stat함수는 0을 반환합니다.
	{
		if ((non_builtin_exec(cmd_list, argv, envp, cmd_list->cmdline[0].cmd, fds)) == -1) // 명령어에 맞게 프로그램을 동작시킵니다.
		{
			free(buf);
			return (0);
		}
		flag = 1;
	}
	else // 명령어에 경로가 포함되지 않은 순수한 명령어일 경우
	{
		if ((env_path = get_env_value("PATH", envp)) == NULL) // 환경변수 PATH에 해당하는 값을 가져옵니다.
		{
			free(buf);
			return (0);
		}
		if ((paths = ft_split(env_path, ':')) == NULL) // PATH에 해당하는 값을 : 문자 기준으로 split 하여 paths 이중포인터 변수에 넣습니다.
		{
			free(buf);
			return (0);
		}
		while (paths[++i] != NULL) // : 로 분리된 path들을 하나씩 볼겁니다.
		{
			if ((tmp = strjoin_path(paths[i], cmd_list->cmdline[0].cmd)) == 0) // path 뒤에 명령어를 붙입니다. (ex. /bin + / + cat)
			{
				free(buf);
				return (0);
			}
			if (cmd_list->cmdline[0].cmd[0] != '\0' &&  stat(tmp, buf) == 0) // path와 명령어를 붙인 문자열에 해당하는 경로에 파일이 있을 경우, 0을 반환(ex. /bin/cat 경로에 해당하는 cat 파일이 존재하므로 0반환)
			{
				if (non_builtin_exec(cmd_list, argv, envp, tmp, fds) == -1) // 명령어에 맞게 프로그램을 동작시킵니다.
				{
					free(buf);
					return (0);
				}
				flag = 1; // 현재 함수를 어떻게 반환할지 결정하는 flag입니다. flag는 0으로 초기화되어 있고, flag가 0일 경우에 현재 함수는 0을 반환하여 오류를 나타냅니다.
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
	if (flag == 0)
	{
		free(buf);
		return (0);
	}
	free(buf);
	return (1);
}

int				exec_function(t_cmd *cmd_list, char *argv[], char **envp[], int fds[])
{
	int			fd;
	int			right_flag;

	if (redir_err_chk(cmd_list) == -1)
		return (-1);
	if ((right_flag = redirect_check(cmd_list, &fds)) == -1) // redirect가 필요한 노드일 경우, redirect 함수를 실행합니다.
		return (-1);
	if (cmd_list->pipe_flag == 1 && right_flag == 0) // pipe_flag가 설정되어 list의 다음 노드가 존재하고 redirection 출력기호가 없을 때, 현재 노드의 출력은 표준출력이 아닌 다음 노드로 넘겨줘야 하므로 fd에 파이프의 입력fd를 넣어줍니다. 그렇지 않을경우, 표준출력 fd인 1을 fd에 넣어줍니다.
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
		return (ft_env(*envp, fd));
	else if (ft_strncmp("export", cmd_list->cmdline[0].cmd, 7) == 0)
		return (ft_export(cmd_list, envp, fd));
	else if (ft_strncmp("echo", cmd_list->cmdline[0].cmd, 5) == 0)
		return (ft_echo(cmd_list, fd));
	else if (ft_strncmp("unset", cmd_list->cmdline[0].cmd, 6) == 0)
		return (ft_unset(cmd_list, *envp));
	else if (non_builtin(cmd_list, argv, *envp, fds) == 0) // 위의 해당하는 명령어가 아닐경우, non_built 함수에서 입력된 명령어가 유효한 명령어인지 최종적으로 확인합니다. 유효한 명령어일 경우, 내장된 프로그램이 실행되고 아닐경우, 오류가 출력됩니다.
	{
		cmd_list->err_manage.errcode = 1;
		return (-1);
	}
	return (0);
}

int				exec(t_cmd *cmd_list, char *argv[], char **envp[])
{
	int			fds[2];
	int			status;
	pid_t		pid;
	pid_t		wpid;
	int			tmp;

	pipe(fds); // 부모프로세스와 자식프로세스간 통신을 위해 pipe를 생성합니다. 크기가 2인 fds배열엔 생성된 pipe의 입출력 fd가 들어갑니다.(입력 : fds[1] == 4, 출력 : fds[0] == 3)
	if ((tmp = exec_function(cmd_list, argv, envp, fds)) == -1) // 명령어에 맞게 프로그램을 실행합니다.
		print_errstr(cmd_list); // 프로그램 실행 도중 오류 발생 시, 오류 메시지를 출력합니다.
	else if (tmp == 1)
		g_exit_status = 0;
	dup2(100, STDOUT); // redirection 기능이 동작하면 입출력 fd는 입출력 기능이 아닌 다른 file을 가리키게 됩니다. 그래서 main에서 backup해뒀던 표준입출력을 가리키는 fd인 100, 101을 이용하여 표준입출력 fd의 기능을 원상복구 시킵니다.
	dup2(101, STDIN);
	if (cmd_list->pipe_flag == 1) // 파이프 처리가 필요할 경우, 자식프로세스를 생성합니다. 파이프 처리가 필요하지 않을경우, 현재 함수를 종료합니다.
	{
		if ((pid = fork()) < 0)
		{
			cmd_list->err_manage.errcode = 1;
			print_errstr(cmd_list);
			return (g_exit_status);
		}
	}
	else
		return (g_exit_status);
	if (pid == 0) // pid로 0을 반환받는 자식프로세스가 실행되는 조건문입니다.
	{
		dup2(fds[0], 0); // 자식프로세스에서 부모프로세스의 표준출력을 받아야하기 때문에 자식프로세스의 표준입력 fd가 부모프로세스의 표준출력을 받는 파이프의 출력 fd인 fds[0]을 가리키게 합니다.
		close(fds[0]); // 사용하지 않는 fd는 닫아줍니다.
		close(fds[1]);
		g_exit_status = exec(cmd_list->next, argv, envp); // 자식프로세스로 실행될 명령어가 동작할 수 있게끔 현재함수를 재귀로 실행시켜줍니다.
		exit(g_exit_status); // 명령어의 동작이 끝나면 자식프로세스를 종료시킵니다.
	}
	else // pid로 자식프로세스의 주소를 반환받는 부모프로세스가 실행되는 조건문입니다.
	{
		close(fds[1]);
		close(fds[0]);
		wpid = waitpid(pid, &status, 0); // 부모프로세스는 자식프로세스가 종료될때까지 waitpid함수에서 대기하고, 자식프로세스가 종료되어 status에 자식프로세스의 종료상태가 입력되면 waitpid함수는 반환됩니다.
		g_exit_status = status >> 8;
		return (g_exit_status);
	}
}
