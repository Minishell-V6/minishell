/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoylee <hoylee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 15:04:56 by hoylee            #+#    #+#             */
/*   Updated: 2021/06/21 16:43:34 by hoylee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_signal(void)
{
	signal(SIGINT, ctrl_c);
	signal(SIGQUIT, ctrl_bs);
	signal(SIGTSTP, ctrl_z);
}
