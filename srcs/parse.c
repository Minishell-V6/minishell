/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djeon <djeon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 14:57:25 by djeon             #+#    #+#             */
/*   Updated: 2021/07/01 18:04:06 by djeon            ###   ########.fr       */
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

	i = 0;
	start = 0;
	pipe_flag = 1;
	while (1) // readline으로 입력받은 line을 모두 하나하나 체크하는 loop입니다.
	{
		if (line[i] == '\0' || line[i] == '|') // 파이프를 기준으로 명령어를 나누기 위해 설정한 조건문입니다. null을 만날 경우, 이전까지의 명령어를 list의 노드로 생성합니다.
		{
			if (line[i] == '|')
				line[i] = '\0'; // 파이프문자를 null로 바꾸어 split을 용이하게 합니다.
			else
				pipe_flag = 0; // 파이프가 아니라 null을 만났을 경우, 마지막 노드이므로 파이프처리를 할 필요가 없기 때문에 pipe_flag를 설정하지 않습니다.
			new = ft_new(&line[start], pipe_flag, 0, start); // list의 노드를 생성합니다.
			ft_alloc_token(new->cmdline, envp);
			if (start == 0) // list의 처음 노드를 가리키는 조건입니다. start 변수는 split할 명령어의 첫번째 index를 가리킬 것입니다. 처음 노드일 경우, list가 없는 상태이기 때문에 next로 연결해주는 것이 아닌, 생성된 구조체를 cmd_list에 바로 넣어줍니다. 그리고 반환을 위해 tmp에 backup해둡니다.
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
