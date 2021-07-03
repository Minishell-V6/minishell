/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_split.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 19:19:26 by sejpark           #+#    #+#             */
/*   Updated: 2021/07/02 19:21:59 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_SPLIT_H
# define CMD_SPLIT_H
# include <stdlib.h>
# include "structs.h"

t_token			*cmd_split(char const *s, char c, int *t_cmd_len);

#endif
