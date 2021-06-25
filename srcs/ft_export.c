/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiylee <jiylee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 14:13:20 by seojeong          #+#    #+#             */
/*   Updated: 2021/06/24 22:59:48 by mac              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void			print_quote(char *str, int fd)
{
	int i;

	i = 0;
	if (haveequal(str))
	{
		while (str[i] != '=')
			i++;
		write(fd, str, ++i);
		write(fd, "\"", 1);
		write(fd, str + i, ft_strlen(str + i));
		write(fd, "\"", 1);
	}
	else
	{
		while (str[i])
			i++;
		write(fd, str, ++i);
		write(fd, "=", 1);
		write(fd, "\"\"", 2);
	}
}

void			print_export(char **envp, int fd)
{
	int		i;
	char	**sorted;

	i = 0;
	sorted = sort_env(envp);
	while (sorted[i])
	{
		ft_putstr_fd("declare -x ", fd);
		print_quote(sorted[i], fd);
		ft_putchar_fd('\n', fd);
		i++;
	}
	free(sorted);
}

int				check_key(char **envp, char *line)
{
	int i;
	int key;

	i = 0;
	key = 0;
	if (haveequal(line))
	{
		while (line[key] != '=')
			key++;
	}
	else
	{
		while (line[key])
			key++;
	}
	while (envp[i])
	{
		if (ft_strncmp(envp[i], line, key) == 0)
			return (i);
		i++;
	}
	return (-1);
}

int				add_envp(t_cmd *cmd_list, char ***envp)
{
	char		**new;
	int			row;
	int			i;

	i = 0;
	row = cnt_envp_row(*envp);
	if (!(new = (char **)malloc(sizeof(char *) * (row + 2))))
		return (0);
	while ((*envp)[i])
	{
		new[i] = ft_strdup((*envp)[i]);
		i++;
	}
	new[i] = ft_strdup(cmd_list->cmdline[1]);
	new[++i] = NULL;
	printf("free-envp\n");
	free(*envp);
	*envp = new;
	printf("free-envp\n");
	return (1);
}

void			ft_export(t_cmd *cmd_list, char ***envp, int fd)
{
	int			i;
	int 		keyindex;

	i = 0;
	if (cmd_list->cmdline[1])
	{
		if (isvalid_export(cmd_list->cmdline[1]))
		{
			if ((keyindex = check_key(*envp, cmd_list->cmdline[1])) >= 0)
			{
				if (haveequal(cmd_list->cmdline[1]))
					add_key_envp(envp, cmd_list, keyindex);
			}
			else
				add_envp(cmd_list, envp);
		}
		else
		{
			cmd_list->err_manage->errcode = 5;
			print_errstr(cmd_list);
		}
	}
	else
		print_export(*envp, fd);
}
