#include "../includes/minishell.h"

void	save_filename(t_cmp *cmd_list, int i, int first, int second)
{
	cmd_list.redirect_filename[first] = cmd_list->token[i].cmd_line;
	cmd_list.redirect_filename[second] = cmd_list->token[i + 1].cmd_line;
}

int		redirect_check(t_cmp *cmd_list)
{
	//여기서 리다이렉션 있는지 확인하고 해당 파일이 정상적인지 테스트함.
	int i = -1;
	while(++i < 4)
		cmd_list->redirect_filename[i] = 0;
	i = 0;
	while(cmd_list->token[i])
	{
		if(cmd_list->token[i].recdirect_flag == 0)
			;
		else if (ft_strncmp("<", cmd_list->token[i].cmd_line, 2) == 0 
							|| ft_strncmp("<<", cmd_list->token[i].cmd_line, 3) == 0)
		{
			fd = open(cmd_list->token[i + 1].cmd_line, O_WRONLY | O_CREAT | O_APPEND, 0744);
			if(fd > 0)	
				save_filename(cmnd_list, i, 0, 1);
			else
			{
				//ERROR not fiound file
				printf("not found file");
			}
			close(fd);
		}
		else if (ft_strncmp(">", cmd_list->token[i].cmd_line, 2) == 0
							|| ft_strncmp(">>", cmd_list->token[i].cmd_line, 3) == 0)
		{
			fd = open(cmd_list->token[i + 1].cmd_line, O_WRONLY | O_CREAT | O_APPEND, 0744);
			if(fd > 0)
				save_filename(cmnd_list, i, 2, 3);
			else
			{
				//ERROR not fiound file
				printf("not found file");
			}
		}
		i++;
	}
	return 0;
}
