#include "minishell.h"

void    ft_echo(t_data *data, t_command *cmd)
{
    int     n;
	int		i;

    n = 0;
	i = 0;
	data->exit_status = 0;
    if (ft_strcmp(cmd->argv[i], "echo") == 0 && ft_count_argument(cmd) > 1)
    {
        while (cmd->argv[i + 1] && check_n(cmd->argv[i + 1]))
        {
            n = 1;
            i++;
        }
	   	i++;
		while (cmd->argv[i])
        {
            printf("%s", cmd->argv[i]);
            if (cmd->argv[i + 1])
                printf(" ");
            i++;
        }
        if (n == 0)
            printf("\n");
    }
	else
		error_process(data, cmd->argv[i], ": command not found", 1);
	return;
    
}

int     check_n(char *str)
{
    int     i;

    i = 2;
    if (str[0] != '-' || str[1] != 'n')
        return (0);
    while (str[i])
    {
        if (str[i] != 'n')
            return (0);
        i++;
    }
    return (1);
}