#include "../includes/minishell.h"

/*
	변수명(*key)을 입력하면 값을 반환해주는 함수입니다.
	export key=value의 경우에만 반환합니다.
*/

char	*get_env_value(char *key, char **envp)
{
	int i;

	i = -1;
	while (envp[++i])
	{
		// env는 key=value 형식이기떄문에 key의 길이까지만 비교하게되면
		// 변수 tmp와 tmpp는 tmp로 같이 조회가 됩니다.
		// 변수명의 다음 인덱스에 '='가 있는지를 조건에 추가했습니다.
		if ((!ft_strncmp(key, envp[i], ft_strlen(key))) && envp[i][ft_strlen(key)] == '=')
			return (envp[i] + ft_strlen(key) + 1);
	}
	// NULL?
	return ("");
}