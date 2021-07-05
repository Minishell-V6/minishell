/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mac <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 21:53:00 by mac               #+#    #+#             */
/*   Updated: 2021/07/05 00:19:44 by mac              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long long		ft_atoi(const char *str, int *err_flag)
{
	int				i;
	int				mark;
	long long		result;

	i = 0;
	mark = 1;
	result = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			mark = -1;
		i++;
	}
	while (str[i] != '\0')
	{
		if (str[i] >= '0' && str[i] <= '9')
			result = result * 10 + (str[i] - '0');
		else
			break ;
		i++;
	}
	if (result < 0)
		*err_flag = 1;
	if (mark == -1 && result == (-9223372036854775807 - 1))
	{
		*err_flag = 0;
		return (result);
	}
	return (mark * result);
}
