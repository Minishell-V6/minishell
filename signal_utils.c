#include "minishell.h"
#include <signal.h>

void		handle_signal(int signo)
{
	// pid_t	pid;
	// int		status;

	// pid = waitpid(-1, &status, WNOHANG);
	if (signo == SIGINT)
	{
		// if (pid == -1)
		// {
        ft_putstr_fd("\b\b  \b\b\n", STDOUT);
        ft_putstr_fd("minishell $ ", STDOUT);
			// g_exit_status = 1;
		// }
		// else
			// ft_putchar_fd('\n', STDOUT);
	}
	else if (signo == SIGQUIT)
	{
		// if (pid == -1)
        ft_putstr_fd("\b\b  \b\b", STDOUT);
		// else
			// ft_putstr_fd("Quit: 3\n", STDOUT);
	}
}

void		set_signal(void)
{
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, handle_signal);
}