/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiylee <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 21:36:55 by jiylee            #+#    #+#             */
/*   Updated: 2020/11/04 15:24:34 by jiylee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	index;

	index = 0;
	while (s[index])
		index++;
	return (index);
}

char	*ft_strdup(const char *s)
{
	char	*newstr;
	int		s_len;
	int		index;

	s_len = ft_strlen(s);
	index = 0;
	if (!(newstr = (char *)malloc(sizeof(char) * (s_len + 1))))
		return (0);
	while (s[index])
	{
		newstr[index] = s[index];
		index++;
	}
	newstr[index] = '\0';
	return (newstr);
}

char	*ft_strjoin(char *store, char *buf)
{
	char	*new_str;
	int		i;
	int		j;

	if (!store)
		return (ft_strdup(buf));
	if (!buf)
		return (0);
	if (!(new_str = (char *)malloc(sizeof(char) *
					(ft_strlen(store) + ft_strlen(buf) + 1))))
		return (0);
	i = -1;
	while (store[++i])
		new_str[i] = store[i];
	free(store);
	store = 0;
	j = -1;
	while (buf[++j])
		new_str[i + j] = buf[j];
	new_str[i + j] = '\0';
	return (new_str);
}
