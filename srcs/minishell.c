/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojeong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 19:52:35 by djeon             #+#    #+#             */
/*   Updated: 2021/06/22 12:18:09 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int				main(int argc, char *argv[], char *envp[])
{
	char		*line;
	t_cmd		*cmd_list;
	char		**cpenv;

	argc = 1;
	cpenv = copy_envp(envp);
	set_signal();
	while ((line = readline("minishell $ ")))
	{
		if (*line != '\0')
		{
			parse(&cmd_list, line);
			if (exec(cmd_list, argv, &cpenv) == -1)
				print_errstr(cmd_list);
			free_all(cmd_list);
			add_history(line);
		}
		free(line);
	}
	ft_putstr_fd("\x1b[1A", STDOUT);
	ft_putstr_fd("\033[12C",STDOUT);
	ft_putstr_fd("exit\n", STDOUT);
	return (0);
}
