/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojeong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 19:52:35 by djeon             #+#    #+#             */
/*   Updated: 2021/06/25 10:59:25 by mac              ###   ########.fr       */
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
	while ((line = readline("minishell $ ")) != NULL)
	{
		add_history(line);
		if (*line != '\0')
		{
			parse(&cmd_list, line);
			exec(cmd_list, argv, &cpenv);
			free_structure(cmd_list);
		}
		free(line);
	}
	return (0);
}
