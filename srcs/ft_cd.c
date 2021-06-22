/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoylee <hoylee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 16:37:25 by hoylee            #+#    #+#             */
/*   Updated: 2021/06/22 12:16:22 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_cd(char *string)
{
	int i;
	char *pst_buffer;	

	i = 0;
	if (string == 0 || string[0] == 0)
	{
		chdir(getenv("HOME"));
		return (0);
	}
	pst_buffer = getcwd(0, 0);
	if (string[0] == '~')
	{
		string = string + 1;
		if(string[0] == '/')
			string = string + 1;
		chdir(getenv("HOME"));
	}
	if (string[0] != 0 && chdir(string) == -1)
	{
		chdir(pst_buffer);
		printf("Error\n");
		return (-1);
	}
	return (0);
}
