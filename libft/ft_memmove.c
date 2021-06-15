/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mac <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 21:49:59 by mac               #+#    #+#             */
/*   Updated: 2020/07/27 21:22:29 by djeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*srcc;
	char	*dstc;
	size_t	i;

	i = 0;
	srcc = (char *)src;
	dstc = (char *)dst;
	if (!dst && !src)
		return (0);
	if (srcc < dstc)
		while (len > 0)
		{
			*(dstc + len - 1) = *(srcc + len - 1);
			len--;
		}
	else
		while (i < len)
		{
			*(dstc + i) = *(srcc + i);
			i++;
		}
	return (dst);
}
