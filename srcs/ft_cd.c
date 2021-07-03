/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoylee <hoylee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 16:37:25 by hoylee            #+#    #+#             */
/*   Updated: 2021/07/03 14:51:17 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_cd(t_cmd *cmd_list)
{ 
	int i;
	char *pst_buffer;	

	i = 0;
	if (cmd_list->cmdline[1].cmd == 0 || cmd_list->cmdline[1].redir_flag == 1)
	{
		chdir(getenv("HOME"));
		return (1);
	}
	if (cmd_list->cmdline[1].cmd[0] == 0)
		return (1);
	pst_buffer = getcwd(0, 0);
	if (cmd_list->cmdline[1].cmd[0] == '~')
	{
		if(cmd_list->cmdline[1].cmd[1] == '/')
		{
			cmd_list->cmdline[1].cmd = ft_substr(cmd_list->cmdline[1].cmd, 1, ft_strlen(cmd_list->cmdline[1].cmd + 1));
			cmd_list -> cmdline[1].cmd = ft_strjoin(getenv("HOME"), cmd_list->cmdline[1].cmd);
		}
		else if(cmd_list->cmdline[1].cmd[1] == 0)
		{
			chdir(getenv("HOME"));
			return (1);
		}
	}
	if (chdir(cmd_list->cmdline[1].cmd) == -1)
	{
		chdir(pst_buffer);
		cmd_list->err_manage.errcode = 3;
		cmd_list->err_manage.errindex = 1;
		return (-1);
	}
	return (1);
}
