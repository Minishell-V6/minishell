/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_split.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 19:19:26 by sejpark           #+#    #+#             */
/*   Updated: 2021/06/25 17:41:21 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_SPLIT_H
# define CMD_SPLIT_H
# include <stdlib.h>

typedef struct	s_token
{
	char		*cmd;
	char		redir_flag;
}				t_token;
t_token			*cmd_split(char const *s, char c);

#endif
