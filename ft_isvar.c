#include "minishell.h"

/*
	변수명이 적합한 지 판단하는 함수입니다.
	변수명으로 영문자, _ , 첫자리만 아니면 숫자가 올 수 있습니다.

	ex) dsasd_sad33 -> ok
		132sadsd -> ko

	예외사항) $0~9는 argument들이 순서대로 저장됩니다.
*/

int		ft_isvar(char *str)
{
	int i;

	i = -1;
	while (str[++i])
	{
		if (!(ft_isalnum(str[i]) || str[i] == '_'))
			return (0);
		else if (ft_isdigit(str[0]))
			return (0);
	}
	return (1);
}
