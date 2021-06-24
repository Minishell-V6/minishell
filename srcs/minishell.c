/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojeong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 19:52:35 by djeon             #+#    #+#             */
/*   Updated: 2021/06/23 17:49:54 by djeon            ###   ########.fr       */
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
		if (*line != '\0')
		{
			parse(&cmd_list, line);
//			while (cmd_list->next != NULL)
//			{
//				printf("%s\n", cmd_list->cmdline[0]);
//				cmd_list = cmd_list->next;
//			}
			if (exec(cmd_list, argv, &cpenv) == -1)
				print_errstr(cmd_list);
//			free_all(cmd_list);
			add_history(line);
		}
		free(line);
	}
	return (0);
}
