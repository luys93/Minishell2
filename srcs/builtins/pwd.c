#include "minishell.h"

void    ft_pwd(t_data *data)
{
    char    *dir;

    dir = getcwd(NULL, 0);
    if (dir == NULL)
    {
        perror("Error");
        return;
    }
    printf("%s\n", dir);
    free(dir);
	data->exit_status = 0;
}
