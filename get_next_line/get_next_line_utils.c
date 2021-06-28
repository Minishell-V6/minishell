/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mac <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 14:58:52 by mac               #+#    #+#             */
/*   Updated: 2020/09/11 12:35:10 by mac              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t		ft_strlen(const char *str)
{
	int		i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
		i++;
	return (i);
}

size_t		ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (size == 1 || src[0] == '\0')
		dest[0] = '\0';
	else if (size == 0)
		j = 0;
	else
	{
		while (i < size - 1 && src[i] != '\0')
		{
			dest[i] = src[i];
			i++;
		}
		if (i < size)
			dest[i] = '\0';
	}
	while (src[j] != 0)
		j++;
	return (j);
}

size_t		ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	dest_len;
	size_t	src_len;
	size_t	i;

	dest_len = 0;
	src_len = 0;
	i = 0;
	dest_len = ft_strlen(dest);
	src_len = ft_strlen(src);
	if (size <= dest_len)
		return (src_len + size);
	while (*dest)
		dest++;
	while ((i < size - dest_len - 1) && src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (src_len + dest_len);
}

char		*ft_strjoin(char *s1, char *s2)
{
	char	*ret;
	size_t	tmp1;
	size_t	tmp2;
	int		i;
	int		j;

	i = 0;
	j = 0;
	tmp1 = ft_strlen(s1);
	tmp2 = ft_strlen(s2);
	if (!(ret = (char *)malloc(sizeof(char) * (tmp1 + tmp2 + 1))))
		return (0);
	if (s1)
	{
		while (s1[i] != '\0')
		{
			ret[i] = s1[i];
			i++;
		}
	}
	free(s1);
	while (s2[j] != '\0')
		ret[i++] = s2[j++];
	ret[i] = '\0';
	return (ret);
}

char		*ft_strdup(const char *src)
{
	char	*str;
	int		size;
	int		i;

	size = 0;
	i = 0;
	while (src[size] != '\0')
		size++;
	if (!(str = (char*)malloc(sizeof(char) * (size + 1))))
		return (0);
	while (src[i] != '\0')
	{
		str[i] = src[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
