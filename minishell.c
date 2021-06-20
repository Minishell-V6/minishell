/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djeon <djeon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 19:52:35 by djeon             #+#    #+#             */
/*   Updated: 2021/06/19 11:47:14 by mac              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				main(int argc, char *argv[], char *envp[])
{
	char		*line;
	t_cmd		*cmd_list;

	argc = 1;
	while ((line = readline("minishell $ ")) != NULL)
	{
		if (*line != '\0')
		{
			parse(&cmd_list, line);
			if (exec(cmd_list, argv, envp) == -1)
				print_errstr(cmd_list);
			free_all(cmd_list);
			add_history(line);
		}
		free(line);
	}
	return (0);
}
