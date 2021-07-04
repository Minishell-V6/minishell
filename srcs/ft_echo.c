#include "../includes/minishell.h"

//수정 필요한 부분 echo는 인자로 여러개를 받을 수 있다. redirection이 아니면 다 받음.
//구조체를 받아서 다 받아야함. 일반 명령어인지 구조체인지 체크.

//echo의 n옵션 체크함수.
int         n_opt_chk(char *cmd)
{
	int i;

	i = 1;
	if (ft_strncmp("-n", cmd, 2) != 0)
		return (0);
	while (cmd[++i])
	{
		if (cmd[i] != 'n')
			return (0);
	}
	return (1);
}

int        ft_echo(t_cmd *cmd_list, int fd)
{
	int flg; //-n 옵션에 대한 플래그
	int i;
	int cnt;

	i = 1;
	flg = 0;
	cnt = 0;
	while (n_opt_chk(cmd_list->cmdline[i].cmd))  //-n 옵션이 중복가능해서 while문을 사용
	{
		//-nnnn 도 가능. -n -n -n 도 가능하게 해야합니다.
		flg = 1;
		i++;
	}
	while (cmd_list->cmdline[i].cmd && cmd_list->cmdline[i].redir_flag == 0) //리다이렉션 제외 출력
	{
		if (cnt != 0)
			write(fd, " ", 1); //여러 명령어나올때 사이사이에만 공백넣기.
		ft_putstr_fd(cmd_list->cmdline[i].cmd, fd);
		i++;
		cnt++;
	}
	if (flg == 0)
		write(fd, "\n", 1);
	return (1);
}
