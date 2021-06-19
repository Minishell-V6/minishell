
#include "minishell.h"
//echo의 n옵션 체크함수.
int         n_opt_chk(char *command)
{
    int i;
    i = 1;
    if (ft_strncmp("-n", command, 2) != 0)
        return (0);
    while (command[++i])
    {
        if (command[i] != 'n')
            return (0);
    }
    return (1);
}
void        ft_echo(char **commands, char *envp[])
{
    int flg; //-n 옵션에 대한 플래그
    int i;

    i = 0;
    flg = 0;
    while (!n_opt_chk(commands[i]))  //-n 옵션이 중복가능해서 while문을 사용
    {
        //-nnnn 도 가능. -n -n -n 도 가능하게 해야합니다.
        flg = 1;
        i++;
    }
    while (commands[i])
    {
        ft_putstr_fd(commands[i], 1);
        ++i;
    }
    if (flg == 0)
        write(1, "\n", 1);
}
