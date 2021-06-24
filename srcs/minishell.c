/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojeong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 19:52:35 by djeon             #+#    #+#             */
<<<<<<< HEAD:srcs/minishell.c
/*   Updated: 2021/06/24 00:07:16 by mac              ###   ########.fr       */
=======
/*   Updated: 2021/06/21 14:37:25 by djeon            ###   ########.fr       */
>>>>>>> 06f0fdd2a6062aa49ddcdbe2ecc298b3a84a9bcd:minishell.c
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
		printf("%s\n", line);
		if (*line != '\0')
		{
			parse(&cmd_list, line);
<<<<<<< HEAD:srcs/minishell.c
			if (exec(cmd_list, argv, &cpenv) == -1)
=======
			if (exec(cmd_list, argv, &envp) == -1)
>>>>>>> 06f0fdd2a6062aa49ddcdbe2ecc298b3a84a9bcd:minishell.c
				print_errstr(cmd_list);
			free_all(cmd_list);
			add_history(line);
		}
		free(line);
	}
	return (0);
}
