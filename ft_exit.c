/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djeon <djeon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 14:56:10 by djeon             #+#    #+#             */
/*   Updated: 2021/06/17 17:51:39 by djeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				ft_exit(t_cmd *cmd_list)
{
	int			i;

	i = -1;
	if (cmd_list->cmdline[1] != NULL && cmd_list->cmdline[2] != NULL)
	{
		cmd_list->err_manage->errcode = 2;
		return (-1);
	}
	printf("exit\n");
	if (cmd_list->cmdline[1] != NULL)
	{
		while (cmd_list->cmdline[1][++i] != '\0')
			if (ft_isdigit(cmd_list->cmdline[1][i]) == 0)
			{
				cmd_list->err_manage->errcode = 4;
				cmd_list->err_manage->errindex = 1;
				print_errstr(cmd_list);
				exit(-1);
			}
	}
	else
		exit(0);
	exit(ft_atoi(cmd_list->cmdline[1]) % 256);
}
