/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojeong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 14:13:14 by seojeong          #+#    #+#             */
/*   Updated: 2021/07/02 14:46:44 by seojeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void			ft_env(char **envp, int fd)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (haveequal(envp[i]))
		{
			ft_putstr_fd(envp[i], fd);
			ft_putchar_fd('\n', fd);
		}
		i++;
	}
}

char			**copy_envp(char **envs)
{
	char	**new;
	int		i;

	i = 0;
	while (envs[++i] != NULL)
		i++;
	if (!(new = malloc(sizeof(char *) * (i + 1))))
		return (NULL);
	i = -1;
	while (envs[++i])
		new[i] = ft_strdup(envs[i]);
	new[i] = NULL;
	return (new);
}
