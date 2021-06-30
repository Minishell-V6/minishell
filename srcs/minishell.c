/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojeong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 19:52:35 by djeon             #+#    #+#             */
/*   Updated: 2021/06/29 21:19:15 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int				main(int argc, char *argv[], char *envp[])
{
	char		*line;
	t_cmd		*cmd_list;
	char		**cpenv;

	dup2(STDIN, 100);
	dup2(STDOUT, 101);
	argc = 1;
	cpenv = copy_envp(envp);
	set_signal();
	while ((line = readline("minishell $ ")))
	{
		add_history(line);
		if (*line != '\0')
		{
			parse(&cmd_list, line, cpenv);
			exec(cmd_list, argv, &cpenv);
			free_structure(cmd_list);
		}
		free(line);
	}
	return (0);
}
