#include "minishell.h"

void    execute_builtins(t_data *data, t_command *cmd, char *str)
{
    if (ft_strcmp(str, "pwd") == 0)
        ft_pwd(data);
    else if (ft_strcmp(str, "cd") == 0)
        ft_cd(data, cmd); 
    else if (ft_strcmp(str, "exit") == 0 )
        ft_exit(data); 
    else if (ft_strcmp(str, "echo") == 0 )
        ft_echo(data, cmd); 
    else if (ft_strcmp(str, "export") == 0)
        ft_export(data, cmd);
    else if (ft_strcmp(str, "unset") == 0)
        ft_unset(data, cmd);
    else if (ft_strcmp(str, "env") == 0 )
        ft_env(data);
}

int     is_builtin(char *str)
{
    if (!str)
        return (1);
    if (ft_strcmp(str, "pwd") == 0)
        return(0);
    else if (ft_strcmp(str, "cd") == 0)
        return(0);
    else if (ft_strcmp(str, "exit") == 0)
        return(0);
    else if (ft_strcmp(str, "echo") == 0)
        return(0);
    else if (ft_strcmp(str, "export") == 0)
        return(0);
    else if (ft_strcmp(str, "unset") == 0)
        return(0);
    else if (ft_strcmp(str, "env") == 0)
        return(0);
    return (1);
}

