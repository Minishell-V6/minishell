/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djeon <djeon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 15:01:44 by djeon             #+#    #+#             */
/*   Updated: 2021/06/16 22:30:37 by hoylee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd			*ft_new(char *line, int pipe_flag, char quote)
{
	t_cmd		*result;

	if (!(result = (t_cmd*)malloc(sizeof(t_cmd))))
		return (NULL);
	result->cmdline = ft_split(line, ' ');
	result->pipe_flag = pipe_flag;
	result->quote = quote;
	result->next = NULL;
	return (result);
}

char			check_quote(char *line)
{
	char		result;
	int			i;

	result = 0;
	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '"' && (result == 0 || result == '"'))
		{
			if (result == '"')
				result = 0; //i 인덱스 " 없애 줘야함. 실행 cdㅇ같은 곳에도 있을ㄷ수 있음
			else
				result = '"';//i 인덱스 " 없애 줘야함.
		}
		if (line[i] == '\'' && (result == 0 || result == '\''))
		{
			if (result == '\'')
				result = 0;
			else
				result = '\'';
		}
		i++;
	}
	return (result);
}
