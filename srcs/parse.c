/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seuyu <seuyu@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 14:57:25 by djeon             #+#    #+#             */
/*   Updated: 2021/07/03 20:22:16 by seuyu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void			parse(t_cmd **cmd_list, char *line, char **envp)
{
	int			i;
	int			start;
	int			pipe_flag;
	t_cmd		*tmp;
	t_cmd		*new;
	int			quote_flag;

	quote_flag = 0;
	i = 0;
	start = 0;
	pipe_flag = 1;
	while (1) // readline으로 입력받은 line을 모두 하나하나 체크하는 loop입니다.
	{
		if ((line[i] == '\"' || line[i] == '\'') && quote_flag == 0) //파이프가 따옴표 안에 들어가는 경우 끊으면 안됨.
            quote_flag = 1;
        else if ((line[i] == '\"' || line[i] == '\'') && quote_flag == 1)
            quote_flag = 0;
		if (line[i] == '\0' || (line[i] == '|' && quote_flag == 0)) // 파이프를 기준으로 명령어를 나누기 위해 설정한 조건문입니다. null을 만날 경우, 이전까지의 명령어를 list의 노드로 생성합니다.
		{
			if (line[i] == '|')
				line[i] = '\0'; // 파이프문자를 null로 바꾸어 split을 용이하게 합니다.
			else
				pipe_flag = 0;
			if ((new = ft_new(&line[start], pipe_flag, envp, start)) == 0)
				return ;
			if (start == 0)
			{
				*cmd_list = new;
				tmp = *cmd_list;
			}
			else // 처음 노드가 아니기 때문에 list가 존재하므로 next로 연결해줍니다.
			{
				(*cmd_list)->next = new;
				*cmd_list = (*cmd_list)->next;
			}
			if (pipe_flag == 0) // 마지막 노드이므로 while loop를 벗어납니다.
				break ;
			start = i + 1; // split할 명령어의 첫번째 index를 파이프의 다음 index로 갱신시켜줍니다.
		}
		i++;
	}
	*cmd_list = tmp; // backup 해놨던 첫번째 명령어의 주소를 cmd_list에 넣어 반환합니다.
}
