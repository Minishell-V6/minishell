/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoylee <hoylee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 16:36:51 by hoylee            #+#    #+#             */
/*   Updated: 2021/06/29 22:17:06 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	save_filename(t_cmd *cmd_list, int i, int first, int second)
{
	cmd_list->redirect_filename[first] = cmd_list->cmdline[i].cmd;
	cmd_list->redirect_filename[second] = cmd_list->cmdline[i + 1].cmd;
}

int				redirect_check(t_cmd *cmd_list)
{
	//여기서 리다이렉션 있는지 확인하고 해당 파일이 정상적인지 테스트함.
	int			i;
	int			fd;

	i = -1;
	while (++i < 4)
		cmd_list->redirect_filename[i] = 0;
	i = 0;
	while (cmd_list->cmdline[i].cmd)
	{
		if (cmd_list->cmdline[i].redir_flag == 0)
			;
		else if (ft_strncmp("<", cmd_list->cmdline[i].cmd, 2) == 0 
							|| ft_strncmp("<<", cmd_list->cmdline[i].cmd, 3) == 0)
		{
			fd = open(cmd_list->cmdline[i + 1].cmd, O_WRONLY | O_CREAT | O_APPEND, 0744);
			if (fd > 0)	
				save_filename(cmd_list, i, 0, 1);
			else
			{
				cmd_list->err_manage->errcode = 3;
				cmd_list->err_manage->errindex = i;
				print_errstr(cmd_list);
			}
			close(fd);
		}
		else if (ft_strncmp(">", cmd_list->cmdline[i].cmd, 2) == 0
							|| ft_strncmp(">>", cmd_list->cmdline[i].cmd, 3) == 0)
		{
			fd = open(cmd_list->cmdline[i + 1].cmd, O_WRONLY | O_CREAT | O_APPEND, 0744);
			if (fd > 0)
				save_filename(cmd_list, i, 2, 3);
		}
		i++;
	}
	return (cmd_list->redirect_filename[0] || cmd_list->redirect_filename[2] ? 1 : 0);
}
