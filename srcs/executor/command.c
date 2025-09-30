#include "minishell.h"


/* esecuzione dei comandi semplici (come cat, grep, ls, clear) */
void    cmd_simple(t_data *data, t_command *cmd)
{
    pid_t   pid;

    if (!cmd || !cmd->argv || !cmd->argv[0] || cmd->argv[0][0] == '\0')
	{
		error_process(data, cmd->argv[0], " command not found", 1);
        return;
	}
    pid = fork();
    if (pid == -1)
        ft_error_process("fork", 1);
    else if (pid == 0)
    {
		execve(cmd->path, cmd->argv, data->env);
		error_case(data, *cmd->argv);
    }
    else
	{
        waitpid(pid, &data->exit_status, 0);
		data->exit_status = WEXITSTATUS(data->exit_status);
	}
	
}

/* esecuzione del comando per la pipe */
void    execute_for_pipe(t_data *data, t_command *cmd)
{
	//write(2, "entra qui ?\n", 15);
	//data->exit_status = 1;
	//int i;
	//i = search_first_builtins(cmd);
    /*if (!cmd || !cmd->argv || !cmd->argv[i])
    {
		printf("qui entra?1\n");
        free_temp(data, 'v');
        exit(127);
    }
    if (cmd->argv[i][0] == '\0')
    {
		printf("qui entra?2\n");
        free_temp(data, 'v');
        exit(127);
    }*/
    if (is_builtin(cmd->argv[0]) == 0)
    {
		//printf("qui entra?3\n");
        execute_builtins(data, cmd, cmd->argv[0]);  //nuovo aggiornamento che sto testando
        free_temp(data, 'v');
        exit(1);
    }
    else if (check_command(data, cmd) == 0)
    {
        // Esegui direttamente senza fork (siamo già in un figlio!)
		//printf("entraaaaaaaaaaaa?\n"); //mettere qui il controllo di accesso al file
		
        if (execve(cmd->path, cmd->argv, data->env) == -1)
        {
			//printf("qui entra?4\n");
            perror(cmd->argv[0]);
            free_temp(data, 'v');
            exit(126);
        }
    }
	//printf("qui cosa passa?\n");
    free_temp(data, 'v');
    exit(127);
    
}

/* ultimo figlio della pipe semplice (senza redirezioni)*/
pid_t    ft_last_child_s(t_data *data, t_command *cmd)
{
    pid_t   pid;

    pid = fork();
    if (pid == -1)
        return (-1);
    else if (pid == 0)
    {
        execute_for_pipe(data, cmd);
        exit(127);
    }
    else
        return(pid);
}

/* figlio della pipe semplice (senza redirezioni) */
pid_t   ft_child_pipe_s(t_data *data, t_command *cmd)
{
    int         fd[2];
    pid_t       pid;

    if (pipe(fd) == -1)
        return (-1);
    pid = fork();
    if (pid == -1)
    {
        free_temp(data, 'v');
        return (-1);
    }
    else if (pid == 0)
    {
        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO);
        close(fd[1]);
        execute_for_pipe(data, cmd);
        free_temp(data, 'v');
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

