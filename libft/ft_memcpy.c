/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mac <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 15:07:11 by mac               #+#    #+#             */
/*   Updated: 2020/07/27 21:12:37 by djeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*result;
	char	*start;

	result = (char*)dst;
	start = (char*)src;
	if (!dst && !src)
		return (0);
	while (n--)
	{
		*result++ = *start++;
	}
	return (dst);
}
