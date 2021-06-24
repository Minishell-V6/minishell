#include "../includes/minishell.h"
#include <signal.h>

void	handle_signal(int signo)
{
	if (signo == SIGINT){
		rl_on_new_line();//입력 받은 것 종료
		rl_redisplay();// 입력받은 것 다시 출력
		ft_putstr_fd("  \n",STDOUT);//다시출력해서 커서가 글자의 끝에 있음.
		rl_on_new_line();
		rl_replace_line("", 0);//readline 초기화
		rl_redisplay();//실행
	}
	else if(signo == SIGQUIT)
	{
		rl_on_new_line();//입력 받은 것 종료
		rl_redisplay();// 입력받은 것 다시 출력
		ft_putstr_fd("  \b\b",STDOUT);
	}
}

void	set_signal(void)
{
    signal(SIGINT, handle_signal);
	signal(SIGQUIT, handle_signal);
}
