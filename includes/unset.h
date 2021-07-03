/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 16:27:53 by sejpark           #+#    #+#             */
/*   Updated: 2021/07/02 15:54:59 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UNSET_H
# define UNSET_H
# include "structs.h"
# include "../libft/libft.h"

int	ft_valid_key(char *key);
int ft_unset(t_cmd *cmd_list, char **envp);

#endif
