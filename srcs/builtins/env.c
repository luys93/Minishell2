#include "minishell.h"

void    ft_env(t_data *data) 
{
    int     i;

    i = 0;
	if (ft_count_argument(data->command) > 1)
	{
        error_process(data, data->command->argv[i], " : to many arguments", 1);
		return;
	}
    while (data->env[i] != NULL)
        printf("%s\n", data->env[i++]);
}
