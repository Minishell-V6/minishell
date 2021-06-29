/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_token.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 21:43:45 by sejpark           #+#    #+#             */
/*   Updated: 2021/06/29 16:21:15 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ALLOC_TOKEN_H
# define FT_ALLOC_TOKEN_H
# include <stdlib.h>
# include "cmd_split.h"
# include "get_parse_size.h"
# include "ft_getenv.h"
# include "redir_chk.h"

int		alloc_d_quote_cnt(char *src, char **dest, char **envp);
int		alloc_s_quote_cnt(char *src, char **dest);
t_token *ft_alloc_token(t_token *token, char **envp);

#endif
