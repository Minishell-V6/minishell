/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoylee <hoylee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 16:37:25 by hoylee            #+#    #+#             */
/*   Updated: 2021/06/16 17:17:15 by hoylee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd(char *string)
{
	int i;
	//char **str_arr;
	//char *str_pwd;

	i = 0;
	//str_arr = ft_split(string, '/');
	if (chdir(string) == -1)
	{
		printf("Error");
	}
	return ;
//	while(str_arr[i])
//	{
//		pstrBuffer = getcwd( strBuffer, _MAX_PATH );
//
//		else if (chdir(string)) == -1)
//			return (0);
//		printf("%d = %s\n", i, str_arr[i]);
//		i++;
//	}

}

//int main(void)
//{
//	ft_cd("we/sd");
//	return (0);
//}
