#include "minishell.h"

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
	char **str;

	if (!line)
		return 0;
	if (line[0] >= '0' && line[0] <= '9')
		return 0;
	str = ft_split(line, '=');
	if (ft_strlen(str[0]) == 0 || ft_strlen(str[1]) == 0)
		return 0;
	return 1;
}
