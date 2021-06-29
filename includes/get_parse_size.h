/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_parse_size.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seuyu <seuyu@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 17:26:20 by seuyu             #+#    #+#             */
/*   Updated: 2021/06/25 17:29:23 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_PARSE_SIZE_H
# define GET_PARSE_SIZE_H
# include "../libft/libft.h" 
# include <stdio.h>

int		env_value_size(char *str, int size, char **envp);
int		env_key_size(char *str);
int		env_cnt(char *str, int *size, char **envp);
int		d_quote_cnt(char *str, int *size, int *flag, char **envp);
int		s_quote_cnt(char *str, int *size, int *flag);
int		get_parse_size(char *str, char **envp);

#endif