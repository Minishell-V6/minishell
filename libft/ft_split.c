/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mac <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 18:46:48 by mac               #+#    #+#             */
/*   Updated: 2020/07/28 20:52:49 by mac              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			valid_str(char str, char charset)
{
	if (str == charset)
		return (1);
	return (0);
}

int			cal_word(char *str, char charset)
{
	int i;
	int cnt;

	i = -1;
	cnt = 0;
	while (str[++i] != '\0')
	{
		if (str[i] == charset && !(valid_str(str[i + 1], charset)))
		{
			if (i != 0 && str[i + 1] != '\0')
				cnt++;
		}
	}
	return (cnt + 1);
}

char		*put_str(char const *str, int i, char charset)
{
	char	*result;
	char	*arr;
	int		tmp;
	int		j;

	j = i;
	tmp = 0;
	arr = (char*)str;
	while (!(valid_str(arr[j], charset)) && arr[j] != '\0')
		j++;
	if (!(result = (char*)malloc(sizeof(char) * (j - i) + 1)))
		return (0);
	while (i < j)
		result[tmp++] = arr[i++];
	result[tmp] = '\0';
	return (result);
}

char		**ft_split(char const *str, char charset)
{
	char	**result;
	char	*arr;
	int		tmp;
	int		i;
	int		index;

	arr = (char*)str;
	i = -1;
	index = 0;
	tmp = cal_word(arr, charset);
	if (!(result = (char**)malloc(sizeof(char*) * (tmp + 1))))
		return (0);
	while (arr[++i] != '\0')
		if (!(valid_str(arr[i], charset)))
		{
			result[index] = put_str(str, i, charset);
			i += (ft_strlen(result[index++]) - 1);
		}
	result[index] = 0;
	return (result);
}
