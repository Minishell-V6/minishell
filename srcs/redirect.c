/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoylee <hoylee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 16:36:03 by hoylee            #+#    #+#             */
/*   Updated: 2021/06/29 22:20:05 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int				left_redirect(t_cmd *cmd_list)
{
	int			fd;

	fd = open(cmd_list->redirect_filename[1], O_RDONLY, 0644);
	if (fd < 0)
	{
		printf("no surch file");
		return (-1);
	}
	dup2(fd, STDIN);
	close(fd);
	return (0);
}

int				left_redirect_double(t_cmd *cmd_list, int **fds)
{
	char		*line;

	while (ft_strncmp((line = readline("> ")), cmd_list->redirect_filename[1], 5))
	{
		ft_putendl_fd(line, (*fds)[1]);
	}
	close((*fds)[1]);
	dup2((*fds)[0], 0);
	close((*fds)[0]);
	pipe((*fds));
	return (0);
}

int				right_redirect(t_cmd *cmd_list)
{
	int			fd;

	fd = open(cmd_list->redirect_filename[3], O_WRONLY | O_CREAT | O_TRUNC, 0744);
	if (fd < 0)
	{
		printf("no surch file");
		return (-1);
	}
	dup2(fd, STDOUT);
	close(fd);
	return (0);
}

int				right_redirect_double(t_cmd *cmd_list)
{
	int			fd;

	fd = open(cmd_list->redirect_filename[3], O_WRONLY | O_CREAT | O_APPEND, 0744);
	if (fd < 0)
	{
		printf("no surch file");
		return (-1);
	}
	dup2(fd, STDOUT);
	close(fd);
	return (0);
}



void	redirect(t_cmd *cmd_list, int **fds)
{
	if (ft_strncmp("<", cmd_list->redirect_filename[0], 2) == 0)
		left_redirect(cmd_list);
	else if (ft_strncmp("<<", cmd_list->redirect_filename[0], 3) == 0)
		left_redirect_double(cmd_list, fds);
	if (ft_strncmp(">", cmd_list->redirect_filename[2], 3) == 0)
		right_redirect(cmd_list);
	else if (ft_strncmp(">>", cmd_list->redirect_filename[2], 3) == 0)
		right_redirect_double(cmd_list);
}

