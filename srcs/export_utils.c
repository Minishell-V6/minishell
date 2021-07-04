/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiylee <jiylee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 16:33:34 by jiylee            #+#    #+#             */
/*   Updated: 2021/06/29 21:27:36 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**sort_env(char **envp)
{
	int		i;
	int		j;
	char	**new;
	char	*temp;

	new = copy_envp(envp);
	i = 0;
	while (new[i])
	{
		j = i + 1;
		while (new[j])
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
	return (new);
}

int		cnt_envp_row(char **envp)
{
	int row;

	row = 0;
	while (envp[row])
		row++;
	return (row);
}

int     isvalid_export(char *line)
{
    char **str_arr = ft_split(line, '=');
    char *key = str_arr[0];
    int i;
    int ret;
    i = 0;
    ret = ft_valid_key(key);
    while(str_arr[i])
    {
        free(str_arr[i]);
        i++;
    }
    free(str_arr);
    return (ret);
}

int		haveequal(char *line)
{
	int i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

void	add_key_envp(char ***envp, char *cmd, int keyindex)
{
	free((*envp)[keyindex]);
	(*envp)[keyindex] = ft_strdup(cmd);
}
