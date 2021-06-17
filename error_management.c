/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djeon <djeon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 16:33:46 by djeon             #+#    #+#             */
/*   Updated: 2021/06/17 16:38:40 by djeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			print_errstr(t_cmd *cmd_list)
{
	if (cmd_list->err_manage->errcode == 1)
		printf("minishell: %s: command not found\n", cmd_list->cmdline[0]);
	else if (cmd_list->err_manage->errcode == 2)
		printf("minishell: %s: too many arguments\n", cmd_list->cmdline[0]);
	else if (cmd_list->err_manage->errcode == 3)
		printf("minishell: %s: No such file or directory\n",
				cmd_list->cmdline[cmd_list->err_manage->errindex]);
	else if (cmd_list->err_manage->errcode == 4)
		printf("minishell: %s: %s: numeric argument required\n",
				cmd_list->cmdline[0],
				cmd_list->cmdline[cmd_list->err_manage->errindex]);
}
