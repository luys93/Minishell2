#include "minishell.h"

//static int search_first_builtins(t_command *cmd);

//controllare il carattere nullo nella pipe

/* pipe con redirezioni */
void    pipe_with_redirection(t_data *data, t_command *cmd)
{
    int         original_stdin;
    int         original_stdout;
    int         cmd_count;
    pid_t       *pids;
    t_command   *curr;
    int         i;

    i = 0;
    curr = cmd;
    original_stdin = dup(STDIN_FILENO);
    original_stdout = dup(STDOUT_FILENO);
    cmd_count = count_commands(cmd);
    pids = malloc(sizeof(pid_t) * cmd_count);
    while (curr && curr->next)
    {
        pids[i] = ft_child_pipe_with_redir(data, curr);
        curr = curr->next;
        i++;
    }
    if (curr)
        pids[i] = ft_last_child_with_redir(data, curr);
    dup2(original_stdin, STDIN_FILENO);
    dup2(original_stdout, STDOUT_FILENO);
    close(original_stdin);
    close(original_stdout);
    i = 0;
    while (i < cmd_count)
    {
        if (pids[i] != 1)
		{
            waitpid(pids[i], &data->exit_status, 0);
			data->exit_status = WEXITSTATUS(data->exit_status);
		}
        i++;
    }
    free(pids);
}

/* pipe senza redirezioni */
void    pipe_simple(t_data *data, t_command *cmd)
{
    int         original_stdin;
    int         original_stdout;
    int         cmd_count;
    pid_t       *pids;
    t_command   *curr;
    int         i;

    i = 0;
    curr = cmd;
    original_stdin = dup(STDIN_FILENO);
    original_stdout = dup(STDOUT_FILENO);
    cmd_count = count_commands(cmd);
    pids = calloc(sizeof(pid_t), cmd_count);
    while (curr && curr->next)
    {
        pids[i] = ft_child_pipe_s(data, curr);
        curr = curr->next;
        i++;
    }
    if (curr)
        pids[i] = ft_last_child_s(data, curr);
    dup2(original_stdin, STDIN_FILENO);
    dup2(original_stdout, STDOUT_FILENO);
    close(original_stdin);
    close(original_stdout);
    i = 0;
    while (i < cmd_count)
    {
        if (pids[i] != -1)
		{
            waitpid(pids[i], &data->exit_status, 0);
			data->exit_status = WEXITSTATUS(data->exit_status);
		}
        i++;
    }
    free(pids);
}

/* funzione che riconosce quale pipe eseguire */
void    ft_pipe(t_data *data, t_command *cmd)
{
    t_command   *curr;
    int         has_redir;

    curr = cmd;
    has_redir = 0;
    while (curr)
    {
        if (curr->rediraction || curr->heredoc_fd != 0 || curr->append)
            has_redir = 1;
        curr = curr->next;
    }
    if (has_redir)
    {
        pipe_with_redirection(data, cmd);
    }
    else
    {
        pipe_simple(data, cmd);
    }
}

/* parte iniziale dell'esecuzione */
void    ft_execution(t_data *data, t_command *cmd)
{
    if (!cmd || !cmd->argv) 
    {
        return;
    }
    if (cmd && cmd->next != NULL)
        ft_pipe(data, cmd);
    else if (cmd && cmd->next == NULL)
    {
        if (!cmd->rediraction && cmd->heredoc_fd == 0 && cmd->append == 0)
        {
            if ((is_builtin(cmd->argv[0]) == 0))
                execute_builtins(data, cmd, cmd->argv[0]);
            else if (check_command(data, data->command) == 0)
                cmd_simple(data, cmd);
        }
        else
        {
            if (is_builtin(cmd->argv[0]) == 0)
                builtin_with_redirection(data, cmd);
            else
                cmd_with_redirection(data, cmd);
        }
    }
    free_path(cmd);
}

void	free_temp(t_data *data, int flag)
{
    if (flag == 'v')
    {
        free_env(data->env);
    }
	if (data->command)
	{
		free_all_cmd(data->command);
		data->command = NULL;
	}
	if (data->tokens)
	{
		free_all_token(data->tokens);
		data->tokens = NULL;
	}
	if (data->input)
	{
		free(data->input);
		data->input = NULL;
	}
}

void free_path(t_command *cmd)
{
    while(cmd)
    {
        if(cmd->path)
        {
            free(cmd->path);
            cmd->path = NULL;
        }
        cmd = cmd->next;
    }
}



int search_first_builtins(t_command *cmd)
{
	int i;

	i = 0;
	while(cmd->argv[i] != NULL)
	{
		if (ft_strcmp(cmd->argv[i], "") == 0)
			i++;
		else
			break;	
	}
	return(i);
}