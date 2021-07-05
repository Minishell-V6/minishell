/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_parse_size.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seuyu <seuyu@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 17:25:19 by seuyu             #+#    #+#             */
/*   Updated: 2021/07/04 22:23:07 by seuyu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_parse_size.h"

//안닫힌 따옴표 체크함수.
int		unclosed_quote(char *str, char quote)
{
	int	index;

	index = 1;
	while (str[index] && str[index] != quote)
		index++;
	if (str[index] == '\0') //안닫힌 경우, str[index]는 null문자가 나옴.
		return (0);
	return (1);
}


// 환경변수에서 Value의 길이를 반환하는 함수입니다.
int		env_value_size(char *str, int size, char **envp)
{
	int index;

	index = -1;
	while (envp[++index])
	{
		if ((!ft_strncmp(&str[1], envp[index], size)) && envp[index][size] == '=') //str[0]의 위치는 $이기때문에 [1]의 위치부터 비교합니다.
		{
			return (ft_strlen(envp[index] + size + 1)); //key=value에서 value의 길이를 반환합니다.
		}
	}
	return (0); //일치하는 key가 없으면 0을 반환.
}


//환경변수에서 key의 길이를 반환하는 함수.
int		env_key_size(char *str)
{
	int index;

	index = 0;
	// 문자열에서 $의 자리부터 시작됩니다. ex) $key

	if (ft_isdigit(str[1])) // 변수명의 첫자리에 숫자가 오는 경우.
		return (1);
	while (str[++index])
	{
		if (!(ft_isalnum(str[index]) || str[index] == '_'))   // 변수명은 영문, '_' , 숫자가 올 수 있음.
			return (index - 1);
	}
	return (index - 1); // i는 변수명을 지나 변수명이 아닌 부분을 가르키기때문에 -1.
}



//환경변수의 key와 value의 길이를 처리해주는 함수입니다.
//key의 길이는 index에 반영되고, value의 길이는 *size에 반영됩니다.
int		env_cnt(char *str, int *size, char **envp)
{
	int index;
	char *status;

	index = 0;
	if (str[1] == '?')
	{
		status = ft_itoa(g_exit_status);
		*size += ft_strlen(status);
		free(status);
		return (1);
	}
	// $가 문자열 끝에 오거나 닫는 쌍따옴표 앞에 오는 경우는 문자로 처리합니다.
	if (str[1] == '\0' || str[1] == '\"')
	{
		*size += 1;
		return (0); //index는 이미 ++되어있기 때문에 0이여야한다.
	}
	index = env_key_size(str); //env_key_size는 key값의 길이만 반환합니다. 인덱스는 $까지 포함해서 1을 더합니다.
	*size += env_value_size(str, index, envp);
	return (index);
}


//쌍따옴표 처리 함수입니다.
int		d_quote_cnt(char *str, int *size, char **envp)
{
	int index;

	index = 1;
	while (str[index] && str[index] != '\"')
	{
		if (str[index] == '$') //쌍따옴표 안의 변수처리.
		{
			index += (env_cnt(&str[index], size, envp) + 1);
		}
		else
		{
			index++;
			(*size)++;
		}
	}
	return (index);
}

// 따옴표 처리 함수입니다.
int		s_quote_cnt(char *str, int *size)
{
	int index;

	index = 1;
	while (str[index] && str[index] != '\'')
	{
		index++;
		(*size)++;
	}
	return (index);
}

// 파싱될 문자열의 할당크기를 파악하는 기능을 하는 함수.
// str은 split처리된 문자열을 받습니다.
int get_parse_size(char *str, char **envp)
{
	int	index;  //index는 파싱 전 문자열의 인덱스를 의미합니다.
	int size;	//size는 파싱 후 할당해야할 문자열의 크기.

	size = 0;
	index = -1;
	while (str[++index]) //따옴표와 변수를 처리하면서 지나가는 index를 반영하기 위해 각 함수들이 인덱스를 반환합니다.
	{
		if (str[index] == '\'' && unclosed_quote(&str[index], '\''))
			index += s_quote_cnt(&str[index], &size);
		else if (str[index] == '\"' && unclosed_quote(&str[index], '\"'))
			index += d_quote_cnt(&str[index], &size, envp);
		else if (str[index] == '$')
			index += env_cnt(&str[index], &size, envp);
		else if (str[index])
			size++;
	}
	return (size); //flag가 1이면 안닫힌 따옴표 에러를 의미.
}
