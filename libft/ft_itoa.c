/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mac <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 16:18:28 by mac               #+#    #+#             */
/*   Updated: 2020/08/25 12:40:58 by mac              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_abs(int n)
{
	int		result;

	if (n < 0)
		result = -1 * n;
	else
		result = n;
	return (result);
}

int		cal_size(int n)
{
	int		size;
	int		tmp;

	size = 1;
	tmp = n;
	if (n < -9)
		size++;
	if (n < 0)
	{
		size++;
		tmp = ft_abs(tmp / 10);
	}
	while (tmp > 9)
	{
		size++;
		tmp = tmp / 10;
	}
	return (size);
}

char	*ft_itoa(int n)
{
	char	*result;
	int		size;
	int		flag;

	flag = 0;
	size = cal_size(n);
	if (!(result = (char*)malloc(size + 1)))
		return (0);
	result[size--] = '\0';
	if (n < 0)
		flag = 1;
	while (size >= 0)
	{
		result[size] = '0' + ft_abs(n % 10);
		n = ft_abs(n / 10);
		size--;
	}
	if (flag == 1)
		result[0] = '-';
	return (result);
}
