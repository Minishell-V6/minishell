/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiylee <jiylee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 14:13:20 by seojeong          #+#    #+#             */
/*   Updated: 2021/06/22 16:47:38 by jiylee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_quote(char *str)
{
	int i;

	i = 0;
	if (haveequal(str))
	{
		while (str[i] != '=')
			i++;
		write(1, str, ++i);
		write(1, "\"", 1);
		write(1, str + i, ft_strlen(str + i));
		write(1, "\"", 1);
	}
	else
	{
		while (str[i])
			i++;
		write(1, str, ++i);
		write(1, "=", 1);
		write(1, "\"\"", 2);
	}
}

void	print_export(char **envp)
{
	int		i;
	char	**sorted;

	i = 0;
	sorted = sort_env(envp);
	while (sorted[i])
	{
		ft_putstr_fd("declare -x ", STDOUT);
		print_quote(sorted[i]);
		ft_putchar_fd('\n', STDOUT);
		i++;
	}
	free(sorted);
}

int		check_key(char **envp, char *line)
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

int		add_envp(t_cmd *cmd_list, char ***envp)
{
	char	**new;
	int		row;
	int		i;

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
	// printf("free-envp\n");
	free(*envp);
	*envp = new;
	// printf("free-envp\n");
	return (1);
}

void	ft_export(t_cmd *cmd_list, char ***envp)
{
	int	i;
	int keyindex;

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
		print_export(*envp);
}
