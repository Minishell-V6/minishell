/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seuyu <seuyu@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 12:36:39 by seuyu             #+#    #+#             */
/*   Updated: 2021/06/28 13:00:53 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_GETENV_H
# define FT_GETENV_H
# include "../libft/libft.h"

char	*get_env_value(char *key, char **envp);
#endif
