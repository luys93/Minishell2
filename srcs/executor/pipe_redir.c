#include "minishell.h"

// Funzione per eseguire un comando in una pipe con redirezioni
void execute_for_pipe_with_redir(t_data *data, t_command *cmd)
{
	
    if (!cmd || !cmd->argv || !cmd->argv[0])
        exit(127);
    // Applica le redirezioni se presenti
    if (cmd->rediraction || cmd->heredoc_fd != 0 || cmd->append)
    {
        if (apply_redirection(data, cmd) == -1)
            exit(1);
    }
    if (is_builtin(cmd->argv[0]) == 0)
    {
        execute_builtins(data, cmd, cmd->argv[0]);  

        exit(0);
    }
    else if (check_command(data, cmd) == 0)
    {
        if (execve(cmd->path, cmd->argv, data->env) == -1)
        {
            perror(cmd->argv[0]);
			data->exit_status = 126;
            exit(126);
        }
    }
    exit(127);
}

pid_t ft_last_child_with_redir(t_data *data, t_command *cmd)
{
    pid_t pid;

    pid = fork();
    if (pid == -1)
        return (-1);
    else if (pid == 0)
    {
        execute_for_pipe_with_redir(data, cmd);
        exit(127);
    }
    else
        return (pid);
}

pid_t ft_child_pipe_with_redir(t_data *data, t_command *cmd)
{
    int     fd[2];
    pid_t   pid;

    if (pipe(fd) == -1)
        return (-1);
    pid = fork();
    if (pid == -1)
        return (-1);
    else if (pid == 0)
    {
        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO);
        close(fd[1]);

        execute_for_pipe_with_redir(data, cmd);
        exit(127);
    }
    else
    {
        close(fd[1]);
        dup2(fd[0], STDIN_FILENO);
        close(fd[0]);
        return (pid);
    }
}

