#include "../includes/minishell.h"
#include <signal.h>

void	handle_signal(int signo)
{
	pid_t	pid;
	int		status;

	pid = waitpid(-1, &status, WNOHANG);
	//-1 : 자식 프로세스를 기다림.
	//status : 자식 프로세스가 종료되면 자식 pid값이 할당 됨.
	//WNOHANG : 자식 프로세스가 종료되지 않아서 pid를 회수할 수 없는 경우 반환값으로 0을 받음.
	if (signo == SIGINT){
		if (pid == -1)
		//pid == -1 : 자식 프로세스가 없는 경우
		{
		rl_on_new_line();//입력 받은 것 종료
		rl_redisplay();// 입력받은 것 다시 출력
		ft_putstr_fd("  \n",STDOUT);//다시출력해서 커서가 글자의 끝에 있음.
		rl_on_new_line();
		rl_replace_line("", 0);//readline 초기화
		rl_redisplay();//실행
		}
		else
		{ //줄바꿈만 해줌
			rl_on_new_line();
			rl_redisplay();// 입력받은 것 다시 출력
			ft_putstr_fd("\n",STDOUT);//다시출력해서 커서가 글자의 끝에 있음.
		}
	}
	else if(signo == SIGQUIT)
	{
		if (pid == -1) //ok.
		{
		rl_on_new_line();//입력 받은 것 종료
		rl_redisplay();// 입력받은 것 다시 출력
		ft_putstr_fd("  \b\b",STDOUT);
		}
		else
		{
			rl_on_new_line();
			rl_redisplay();// 입력받은 것 다시 출력
			ft_putstr_fd("Quit: 3\n",STDOUT);//다시출력해서 커서가 글자의 끝에 있음.
			// 여기서 미니쉘 종료해야함.
		}
	}
}

void	set_signal(void)
{
    signal(SIGINT, handle_signal);
	signal(SIGQUIT, handle_signal);
}
