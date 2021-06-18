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

int		isvalid_export(char *line){
	char **str;

	if (!line)
		return 0;
	if (line[0] >= '0' && line[0] <= '9')
		return 0;
	str = ft_split(line, '=');
	if (ft_strlen(str[0]) == 0 || ft_strlen(str[1]) == 0)
		return 0;
	return 1;
}

void	remove_char(char *str, char c)
{
	int		new;
	int		i;

	new = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] != c)
			str[new++] = str[i];
		i++;
	}
	str[new] = 0;
}

int		cnt_envp_row(char **envp)
{
	int row;

	row = 0;
	while(envp[row])
		row++;
	return row;
}

int		add_envp(t_cmd *cmd_list, char ***envp)
{
	char** new;
	int row;
	int i;

	i = 0;
	row = cnt_envp_row(*envp);
	if(!(new = (char **)malloc(sizeof(char*)*(row + 2))))
		return 0;
	while ((*envp)[i])
	{
		new[i] = ft_strdup((*envp)[i]);
		i++;
	}
	new[i] = ft_strdup(cmd_list->cmdline[1]);
	new[++i] = NULL;
	free(*envp);
	*envp = new;
	return 1;
}

void	ft_export(t_cmd *cmd_list, char ***envp)
{
	int	i;
	int error;

	i = 0;
	if (cmd_list->cmdline[1])
	{
		if (isvalid_export(cmd_list->cmdline[1]))
		{
			remove_char(cmd_list->cmdline[1], '\\');
			error = add_envp(cmd_list, envp);
		}
	}
	else
		print_envp(*envp);
}

