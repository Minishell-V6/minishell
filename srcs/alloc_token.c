/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seuyu <seuyu@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 21:42:57 by sejpark           #+#    #+#             */
/*   Updated: 2021/07/04 22:23:17 by seuyu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/alloc_token.h"

int		get_envkey(char *src, char **key)
{
	int	key_len;

	key_len = env_key_size(src);
	*key = ft_substr(src, 1, key_len);
	return (key_len);
}

int		alloc_env(char *src, char **dest, char **envp)
{
	int src_idx;
	char *key;
	char *env_val;
	int env_len;
	char *status;

	src_idx = 0;

	if (src[1] == '?')
	{
		status = ft_itoa(g_exit_status);
		ft_memcpy(*dest, status, ft_strlen(status));
		*dest += ft_strlen(status);
		// ft_strlcpy(dest, status, ft_strlen(status));
		free(status);
		return (1);
	}
	// $가 문자열 끝에 오거나 닫는 쌍따옴표 앞에 오는 경우는 문자로 처리합니다.
	if (src[1] == '\0' || src[1] == '\"')
	{
		**dest = '$';
		*dest += 1;
		return (0);//index는 이미 ++되어있기 때문에 0이여야한다.
	}
	src_idx = get_envkey(src, &key); //env_key_size는 key값의 길이만 반환합니다. 인덱스는 $까지 포함해서 1을 더합니다.
	env_val = get_env_value(key, envp);
	env_len = ft_strlen(env_val);
	ft_memcpy(*dest, env_val, env_len);
	*dest += env_len;
	free(key);
	return (src_idx);
}

int		alloc_d_quote_cnt(char *src, char **dest, char **envp)
{
	int src_idx;

	src_idx = 1;
	while (src[src_idx] && src[src_idx] != '\"')
	{
		if (src[src_idx] == '$') //쌍따옴표 안의 변수처리.
			src_idx += (alloc_env(&src[src_idx], dest, envp) + 1);
		else
		{
			**dest = src[src_idx];
			(*dest)++;
			src_idx++;
		}
	}
	return (src_idx);
}

int		alloc_s_quote_cnt(char *src, char **dest)
{
	int src_idx;
	int dest_len;

	src_idx = 1;
	dest_len = 0;
	while (src[src_idx] && src[src_idx] != '\'')
	{
		src_idx++;
		dest_len++;
	}
	ft_memcpy(*dest, src + 1, dest_len);
	*dest += dest_len;
	return (src_idx);
}

void ft_copy_str(char *src, char *dest, char **envp)
{
	int src_idx;
	int size;
	char *dest_end;

	size = 0;
	src_idx = -1;
	dest_end = dest;
	while (src[++src_idx])
	{
		if (src[src_idx] == '\'' && unclosed_quote(&src[src_idx], '\''))
			src_idx += alloc_s_quote_cnt(&src[src_idx], &dest_end);
		else if (src[src_idx] == '\"' && unclosed_quote(&src[src_idx], '\"'))
			src_idx += alloc_d_quote_cnt(&src[src_idx], &dest_end, envp);
		else if (src[src_idx] == '$')
			src_idx += alloc_env(&src[src_idx], &dest_end, envp);
		else if (src[src_idx])
		{
			*dest_end = src[src_idx];
			dest_end++;
		}
	}
	*dest_end = '\0';
}

t_token *ft_alloc_token(t_token *token, char **envp)
{
	int		cmd_len;
	size_t	i;
	char	*tmp_cmd;

	i = 0;
	while (token[i].cmd)
	{
		cmd_len = 0;
		tmp_cmd = token[i].cmd;
		cmd_len = get_parse_size(tmp_cmd, envp);
		if (token[i].cmd[0] == '<' || token[i].cmd[0] == '>')
		{
			if (redir_chk(token[i].cmd))
				token[i].redir_flag = 1;
			else
				token[i].redir_flag = -1;
		}
		token[i].cmd = (char*)malloc(sizeof(char) * (cmd_len + 1));
		ft_copy_str(tmp_cmd, token[i].cmd, envp);
		free(tmp_cmd);
		i++;
	}
	return (token);
}
