/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiylee <jiylee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 19:48:29 by jiylee            #+#    #+#             */
/*   Updated: 2021/06/22 16:42:42 by jiylee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "../minishell.h"

int				is_newline(char *store)
{
	int			i;

	i = 0;
	while (store[i])
	{
		if (store[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

int				fill_line(char **store, char **line, int i)
{
	char		*p_next;

	(*store)[i] = '\0';
	if ((*line = ft_strdup(*store)) == 0)
		return (-1);
	i++;
	if ((p_next = ft_strdup(*store + i)) == 0)
		return (-1);
	free(*store);
	*store = p_next;
	return (1);
}

int				get_next_line(int fd, char **line)
{
	static char	*store;
	char		buf[BUFFER_SIZE + 1];
	int			read_size;
	int			i;

	ft_putstr_fd("minishell $ ", STDOUT);
	if (line == 0 || fd < 0 || BUFFER_SIZE <= 0 || read(fd, buf, 0) < 0)
		return (-1);
	while ((read_size = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[read_size] = '\0';
		store = ft_strjoin(store, buf);
		if ((i = is_newline(store)) != -1)
			return (fill_line(&store, line, i));
	}
	if (store && (i = is_newline(store)) != -1)
		return (fill_line(&store, line, i));
	if (store)
	{
		*line = ft_strdup(store);
		free(store);
		store = 0;
		return (0);
	}
	*line = ft_strdup("");
	return (0);
}
