/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 16:27:21 by sejpark           #+#    #+#             */
/*   Updated: 2021/07/01 13:28:25 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/unset.h"

int ft_find_envkey(char *key, char **envp)
{
	int i;
	size_t key_len;

	i = 0;
	key_len = ft_strlen(key);
	while (envp[i])
	{
		if (ft_strncmp(key, envp[i], key_len) == 0 && envp[i][key_len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

void ft_delete_env(int tgt_idx, char **envp)
{
	free(envp[tgt_idx]);
	while (envp[tgt_idx])
	{
		envp[tgt_idx] = envp[tgt_idx + 1];
		tgt_idx++;
	}
}

void ft_unset(t_cmd *cmd_list, char **envp)
{
	int i;
	int tgt_idx;

	i = 0;
	while (cmd_list->cmdline[i].cmd)
	{
		tgt_idx = ft_find_envkey(cmd_list->cmdline[i].cmd, envp);
		if (tgt_idx > -1)
			ft_delete_env(tgt_idx, envp);
		i++;
	}
}
