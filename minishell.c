/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojeong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 19:52:35 by djeon             #+#    #+#             */
/*   Updated: 2021/06/17 16:32:48 by seojeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// char	**g_envp = NULL;

int				main(int argc, char *argv[], char *envp[])
{
	char		*line;
	t_cmd		*cmd_list;

	argc = 1;
	// g_envp = envp;
	envp[0] = "Hello";
	while ((line = readline("minishell $ ")) != NULL)
	{
		parse(&cmd_list, line);
		exec(cmd_list, argv, envp);
	}
	add_history(line);
	return (0);
}
