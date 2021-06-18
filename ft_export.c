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

char	**sort_env(char **envp)
{
	int	i;
	int j;
	char **new;
	char *temp;

	new = copy_envp(envp);
	i = 0;
	while (new[i])
	{
		j = i + 1;
		while(new[j])
		{
			if (ft_strncmp(new[i], new[j], ft_strlen(new[i])) > 0)
			{
				temp = new[i];
				new[i] = new[j];
				new[j] = temp;
			}
			j++;
		}
		i++;
	}
	return new;
}
void	print_quote(char *str)
{
	int i;

	i = 0;
	while(str[i] != '=')
	{
		i++;
	} 
	i++;
	write(1, str, i);
	write(1, "\"", 1);
	write(1, str+i, ft_strlen(str+i));
	write(1, "\"",1);
}


void	print_export(char **envp)
{
	int	i;
	
	i = 0;
	char **sorted;
	
	sorted = sort_env(envp);
	while (sorted[i])
	{
		ft_putstr_fd("declare -x ", STDOUT);
		print_quote(sorted[i]);
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

int		check_key(char **envp, char *line)
{
	int i;
	int key;

	i = 0;
	key = 0;
	while (line[key] != '=')
		key++;
	while(envp[i])
	{
		if(ft_strncmp(envp[i], line, key) == 0)
			return i;
		i++;
	}
	return -1;
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
	int keyindex;

	i = 0;
	if (cmd_list->cmdline[1])
	{
		if (isvalid_export(cmd_list->cmdline[1]))
		{
			remove_char(cmd_list->cmdline[1], '\\');
			// 이미 key가 존재하는 경우
			if ((keyindex = check_key(*envp, cmd_list->cmdline[1])) >= 0)
			{
				free((*envp)[keyindex]);
				(*envp)[keyindex] = ft_strdup(cmd_list->cmdline[1]);
			}
			else
				error = add_envp(cmd_list, envp);
		}
	}
	else
		print_export(*envp);
}

