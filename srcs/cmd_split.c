/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 15:33:09 by sejpark           #+#    #+#             */
/*   Updated: 2021/07/04 17:09:56 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cmd_split.h"

static int		ft_split_cnt(char const *s, const char c)
{
	int cnt;
	int begin;
	int quote;
	int redir;

	cnt = 0;
	begin = 0;
	quote = 0;
	redir = 0;
	while (*s)
	{
		if (*s == '"' && (quote == 0 || quote == '"'))
		{
			if (quote == '"')
				quote = 0;
			else
				quote = '"';
		}
		else if (*s == '\'' && (quote == 0 || quote == '\''))
		{
			if (quote == '\'')
				quote = 0;
			else
				quote = '\'';
		}
		if (begin == 0)
		{
			if (*s != c)
				begin = 1;
			if (*s == '<' || *s == '>')
				redir++;
		}
		else
		{
			if (*s == c && quote == 0)
			{
				if (redir)
					redir = 0;
				begin = 0;
				cnt++;
			}
			else if ((*s == '>' || *s == '<') && quote == 0)
			{
				if (redir == 0 && *(s - 1) != ' ')
				{
					cnt++;
				}
				redir++;
			}
			else if (*s != c && *s != '\''
						&& !(*s == '>' || *s == '<')
						&& quote == 0
						&& (*(s - 1) == '>' || *(s - 1) == '<'))
			{
				if (redir)
					redir = 0;
				cnt++;
			}
			else if (*s == '\'' && quote == '\''
						&& (*(s - 1) == '>' || *(s - 1) == '<'))
			{
				if (redir)
					redir = 0;
				cnt++;
			}
			else if (*s == '"' && quote == '"'
						&& (*(s - 1) == '>' || *(s - 1) == '<'))
			{
				if (redir)
					redir = 0;
				cnt++;
			}
		}
		s++;
	}
	return (begin == 0 ? cnt : cnt + 1);
}

static int		ft_word_len(char const *s, const char c)
{
	int len;
	int begin;
	int quote;

	len = 0;
	begin = 0;
	quote = 0;

	if (*s == '>' || *s == '<')
	{
		while (*s)
		{
			if (*s == '>' || *s == '<')
				len++;
			else
				return (len);
			s++;
		}
	}
	while (*s)
	{
		if (*s == '"' && (quote == 0 || quote == '"'))
		{
			if (quote == '"')
				quote = 0;
			else
				quote = '"';
		}
		else if (*s == '\'' && (quote == 0 || quote == '\''))
		{
			if (quote == '\'')
				quote = 0;
			else
				quote = '\'';
		}
		if (begin == 0)
		{
			if (*s != c)
			{
				begin = 1;
				len++;
			}
		}
		else
		{
			if (*s == c && quote == 0)
				break ;
			else if ((*s == '>' || *s == '<') && quote == 0)
				break ;
			else
				len++;
		}
		s++;
	}
	return (len);
}

static char	*ft_alloc_word(int *idx, char const *s, const char c)
{
	int		word_len;
	char	*word;
	int		i;

	word_len = ft_word_len(&s[*idx], c);
	word = (char*)malloc(sizeof(char) + (word_len + 1));
	if (word == NULL)
		return (NULL);
	i = 0;
	while (i < word_len)
	{
		word[i] = s[*idx + i];
		i++;
	}
	word[i] = '\0';
	*idx += word_len;
	return (word);
}

static void	*ft_free(t_token *result, int len)
{
	int i;

	i = 0;
	while (i < len)
		free(result[i++].cmd);
	return (NULL);
}

t_token	*cmd_split(char const *s, char c)
{
	int		i;
	int		cursor;
	t_token	*result;

	if (s == NULL)
		return (NULL);
	i = 0;
	cursor = 0;
	result = (t_token*)malloc(sizeof(t_token) * (ft_split_cnt(s, c) + 1));
	if (result == NULL)
		return (NULL);
	while (s[cursor])
	{
		if (s[cursor] == c)
			cursor++;
		else
		{
			result[i].cmd = ft_alloc_word(&cursor, s, c);
			result[i].redir_flag = 0;
			if (result[i].cmd == NULL)
				return (ft_free(result, i));
			i++;
		}
	}
	result[i].cmd = 0;
	return (result);
}
