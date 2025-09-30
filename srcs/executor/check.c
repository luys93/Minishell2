#include "minishell.h"

//static int is_file(const char *path);

/* aggiustare /bin/ls non funziona, mettere un check, che il path esista già */
char *search_path(char *cmd, char **env)
{
    char    **all_paths;
    char    *full_path;
    char    *temp;
    int     i;

    i = 0;
    while (env[i] && ft_strnstr(env[i], "PATH", 4) == 0)
        i++;
    if (!env[i])
        return(NULL);
    all_paths = ft_split(env[i] + 5, ':');
    i = 0;
    while (all_paths[i])
    {
        temp = ft_strjoin(all_paths[i], "/");
        full_path = ft_strjoin(temp, cmd);
        free(temp);
        if (full_path && access(full_path, F_OK | X_OK) == 0) 
            return (ft_free_array(all_paths), full_path);
        free(full_path);
        i++;
    }
    return (ft_free_array(all_paths), NULL);
}

int     command_exists(t_data *data, t_command *cmd)
{
    char    *path_cmd;

    if (!cmd->argv || !cmd->argv[0])
    {
        return(1);
    }
	if(ft_strchr(*cmd->argv, '/'))
	{
		if(access(cmd->argv[0], X_OK) != 0)
		{
			error_case(data, cmd->argv[0]);
			return(1);
		}
		cmd->path = strdup(cmd->argv[0]);
		return(0);
	}
    path_cmd = search_path(cmd->argv[0], data->env);
    if (!path_cmd)
    {
		ft_putstr_fd("minishell: ", STDERR_FILENO);
        ft_putstr_fd(cmd->argv[0], STDERR_FILENO); // con printf ci sono leak
        ft_putstr_fd(": command not found\n", STDERR_FILENO);
		data->exit_status = 127;
        return(1);
    }
    cmd->path = path_cmd;
    return(0);
}

/* funzione di controllo del comando */
int     check_command(t_data *data, t_command *cmd)
{
    if (command_exists(data, cmd))
        return(1);
    return (0);
}

