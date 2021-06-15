/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mac <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 14:55:14 by mac               #+#    #+#             */
/*   Updated: 2020/09/14 10:43:36 by mac              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int			new_line(char *result)
{
	int		i;

	i = 0;
	while (result[i])
	{
		if (result[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

int			before_newline(char **result, int line_tmp, char **line)
{
	int		size;
	char	*tmp;

	tmp = 0;
	size = ft_strlen(*result + line_tmp);
	(*result)[line_tmp] = '\0';
	*line = ft_strdup(*result);
	if (size > 0)
		tmp = ft_strdup(*result + line_tmp + 1);
	free(*result);
	*result = tmp;
	return (1);
}

int			last_return(char **result, char **line)
{
	int			line_tmp;

	if (*result && ((*result)[0] != '\0'))
	{
		line_tmp = new_line(*result);
		if (line_tmp > -1)
			return (before_newline(result, line_tmp, line));
		else
		{
			*line = *result;
			*result = 0;
		}
		return (0);
	}
	else
		*line = ft_strdup("");
	return (0);
}

int			get_next_line(int fd, char **line)
{
	char		buffer[BUFFER_SIZE + 1];
	static char	*result[OPEN_MAX];
	int			read_size;
	int			line_tmp;

	if (fd < 0 || BUFFER_SIZE <= 0 || line == 0)
		return (-1);
	while ((read_size = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		buffer[read_size] = '\0';
		result[fd] = ft_strjoin(result[fd], buffer);
		line_tmp = new_line(result[fd]);
		if (line_tmp > -1)
			return (before_newline(&result[fd], line_tmp, line));
	}
	if (read_size < 0)
		return (-1);
	return (last_return(&result[fd], line));
}
