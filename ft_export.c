/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojeong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 14:13:20 by seojeong          #+#    #+#             */
/*   Updated: 2021/06/17 16:54:24 by seojeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_envp(char **envp)
{
	int	i;
	
	i = 0;
	while (envp[i])
	{
		ft_putstr_fd(envp[i], STDOUT);
		ft_putchar_fd('\n', STDOUT);
		i++;
	}
}

void	add_envp(char *str, char **new, int	i)
{
	new[i] = ft_strdup(str);
	new[i + 1] = NULL;
}

void	ft_export(t_cmd *cmd_list, char **envp)
{
	// int	i;
	// char **new;
	
	cmd_list->cmdline[1] = "hello";
	// i = 0;
	// if (cmd_list->cmdline[1])
	// 	add_envp(cmd_list->cmdline[1], new, i);
	// else
		print_envp(envp);
		
	
}

