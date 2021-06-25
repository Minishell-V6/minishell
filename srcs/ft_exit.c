/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djeon <djeon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 14:56:10 by djeon             #+#    #+#             */
/*   Updated: 2021/06/25 11:19:32 by mac              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int				check_digit(t_cmd *cmd_list)
{
	int			i;

	i = -1;
	while (cmd_list->cmdline[1][++i] != '\0')
		if (ft_isdigit(cmd_list->cmdline[1][i]) == 0)
		{
			cmd_list->err_manage->errcode = 4;
			cmd_list->err_manage->errindex = 1;
			print_errstr(cmd_list);
			if (cmd_list->exit_flag == 1)
				exit(-1);
			else
				return (0);
		}
	return (1);
}

int				ft_exit(t_cmd *cmd_list)
{
	if (cmd_list->exit_flag == 1)
		printf("exit\n");
	if (cmd_list->cmdline[1] != NULL)
	{
		if (check_digit(cmd_list) == 0)
			return (0);
		if (cmd_list->cmdline[1] != NULL && cmd_list->cmdline[2] != NULL)
		{
			cmd_list->err_manage->errcode = 2;
			return (-1);
		}
	}
	else if (cmd_list->exit_flag == 1)
		exit(0);
	if (cmd_list->exit_flag == 1)
		exit(ft_atoi(cmd_list->cmdline[1]) % 256);
	return (0);
}
