/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djeon <djeon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 14:57:25 by djeon             #+#    #+#             */
/*   Updated: 2021/06/29 21:21:09 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void			parse(t_cmd **cmd_list, char *line, char **envp)
{
	int			i;
	int			start;
	int			pipe_flag;
	t_cmd		*tmp;
	t_cmd		*new;

	i = 0;
	start = 0;
	pipe_flag = 1;
	while (1)
	{
		if (line[i] == '\0' || line[i] == '|')
		{
			if (line[i] == '|')
				line[i] = '\0';
			else
				pipe_flag = 0;
			new = ft_new(&line[start], pipe_flag, check_quote(line), start);
			ft_alloc_token(new->cmdline, envp);
			if (start == 0)
			{
				*cmd_list = new;
				tmp = *cmd_list;
			}
			else
			{
				(*cmd_list)->next = new;
				*cmd_list = (*cmd_list)->next;
			}
			if (pipe_flag == 0)
				break ;
			start = i + 1;
		}
		i++;
	}
	*cmd_list = tmp;
}
