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

int		mv_home(void)
{
		chdir(getenv("HOME"));
		return (1);
}

int		put_err_data(t_cmd *cmd_list, int errcode, int errindex)
{
	cmd_list->err_manage.errcode = errcode;
	cmd_list->err_manage.errindex = errindex;
	return (-1);
}

int		ft_cd(t_cmd *cmd_list)
{ 
	int i;
	char *pst_buffer;	

	i = 0;
	if (cmd_list->cmdline[1].cmd == 0 || cmd_list->cmdline[1].redir_flag == 1)
		return (mv_home());
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
			return (mv_home());
	}
	if (chdir(cmd_list->cmdline[1].cmd) == -1)
	{
		chdir(pst_buffer);
		return (put_err_data(cmd_list, 3, 1));
	}
	return (1);
}
