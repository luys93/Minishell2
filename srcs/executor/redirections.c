#include "minishell.h"

int     apply_redirection(t_data *data, t_command *cmd)
{
    t_dir   *redir;
    int     status;

    redir = cmd->rediraction;
    while (redir)
    {
        if (ft_strcmp(redir->type, "<") == 0)
            status = handle_input_redir(data, redir->file);
        else if (ft_strcmp(redir->type, ">") == 0)
            status = handle_output_redir(data, redir->file);
        else if (ft_strcmp(redir->type, ">>") == 0)
            status = handle_append_redir(data, redir->file);
		else if (ft_strcmp(redir->type, "<<") == 0)
			status = handle_heredoc_redir(cmd);
        if (status == -1)
            return (-1);
        redir = redir->next;
    }
    return(0);
}

void    cmd_with_redirection(t_data *data, t_command *cmd)
{
    pid_t   pid;

    if (check_command(data, data->command) != 0)
        return;
    pid = fork();
    if (pid < 0)
        ft_error_process("fork", 1);
    else if (pid == 0)
    {
        if (apply_redirection(data, cmd) == -1)
           exit(1);
		if(cmd->heredoc_fd)
			return;
        if (execve(cmd->path, cmd->argv, data->env) == -1)
            ft_error_process("execve", 1);
    }
    else
	{
        waitpid(pid, &data->exit_status, 0);
		data->exit_status = WEXITSTATUS(data->exit_status);
	}
}

void    builtin_with_redirection(t_data *data, t_command *cmd)
{
    int     original_stdout;
    int     original_stdin;

    // Salva i file descriptor originali
    original_stdout = dup(STDOUT_FILENO);
    original_stdin = dup(STDIN_FILENO);
    
    // Applica le redirezioni
    if (apply_redirection(data, cmd) == -1)
    {
        close(original_stdout);
        close(original_stdin);
        exit(1);
    }
    
    // Esegui il builtin
    execute_builtins(data, cmd, cmd->argv[0]); //lo sto testando

    // Ripristina i file descriptor originali
    dup2(original_stdout, STDOUT_FILENO);
    dup2(original_stdin, STDIN_FILENO);
    close(original_stdout);
    close(original_stdin);
}
