#include "minishell.h"

//static int error_case(t_data *data);


void    error_process(t_data *data, char *argv, char *str, int status)
{
    ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(argv, 2);
	ft_putstr_fd(":", 2);
    ft_putstr_fd(str, 2);
    ft_putchar_fd('\n', 2);
    data->exit_status = status;
}

int    ft_file(t_data *data, char *filename, int flag)
{
    int     fd;

    fd = -1;
    if (flag == 1)
	{
		//printf("entra qui?1\n");
        fd = open(filename, O_RDONLY);
		if(fd == -1)
		{
				error_process(data, data->command->argv[0], " No such file or directory", 1);
		}
	}
    else if (flag == 2)
	{
		//printf("entra qui?2\n");
        fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if(fd == -1)
        {
			    error_process(data, data->command->argv[0], " Permission denied", 1);
        }
    }
    else if (flag == 3)
	{
			//printf("entra qui?3\n");
        fd = open(filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
		if(fd == -1)
        {	
			    error_process(data, data->command->argv[0], " Permission denied", 1);
        }
    }
   	else if (fd == -1)
	{
		//printf("entra qui?5\n");
        error_case(data, filename);
	}
    return(fd);
}

/*  controlla se c'e un file negli argomenti 
    torna o quando non trova il file, senno
    torna la posizione nell'array di argv */
/*int     check_file(t_command *cmd)
{
    int     i;

    i = 1; //parto da uno perche il primo argomento lo abbiamo controllato, quindi sappiamo che e un comando
    if (!cmd || !cmd->argv)
        return(0);
    while (cmd->argv[i])
    {
        if(access(cmd->argv[i], F_OK) == 0)
        {
            if (access(cmd->argv[i], R_OK) == 0)
                return (i);
            else
            {
                ft_printf("file non disponibile");
                return(0);
            }
        }
        i++;
    }
    return(0);
}*/

void    ft_error_process(char *str, int status)
{
    ft_putstr_fd("minishell: ", 2);
    ft_putstr_fd(str, 2);
    ft_putchar_fd('\n', 2);
    exit(status);
}

int     count_commands(t_command *cmd)
{
    t_command   *curr;
    int         i;

    i = 0;
    curr = cmd;
    while (curr)
    {
        i++;
        curr = curr->next;
    }
    return(i);
}


void error_case(t_data *data, const char *path)
{
	struct stat st;

   
	if(stat(path, &st) == -1)
	{
		//data->exit_status = 127;
		error_process(data, data->command->argv[0], " No such file or directory", 127);
	}
	else if(S_ISDIR(st.st_mode))
	{
		//data->exit_status = 126;
		error_process(data, data->command->argv[0], " Is a directory", 126);
	}
	else if(access(path, X_OK) == -1)
	{
		//data->exit_status = 126;
		error_process(data, data->command->argv[0], " Permission denied", 126);
	}
	
}