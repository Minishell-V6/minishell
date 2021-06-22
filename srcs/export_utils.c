#include "../includes/minishell.h"

char	**sort_env(char **envp)
{
	int	i;
	int j;
	char **new;
	char *temp;

	new = copy_envp(envp);
	i = 0;
	while (new[i])
	{
		j = i + 1;
		while(new[j])
		{
			if (ft_strncmp(new[i], new[j], ft_strlen(new[i])) > 0)
			{
				temp = new[i];
				new[i] = new[j];
				new[j] = temp;
			}
			j++;
		}
		i++;
	}
	return new;
}

void	remove_char(char *str, char c)
{
	int		new;
	int		i;

	new = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] != c)
			str[new++] = str[i];
		i++;
	}
	str[new] = 0;
}

int		cnt_envp_row(char **envp)
{
	int row;

	row = 0;
	while(envp[row])
		row++;
	return row;
}

int		isvalid_export(char *line){

	if (line[0] >= '0' && line[0] <= '9')
		return 0;
	return 1;
}

int		haveequal(char *line){
	int i;

	i = 0;
	while(line[i])
	{
		if(line[i] == '=')
			return 1;
		i++;
	}
	return 0;
}
