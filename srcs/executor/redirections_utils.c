#include "minishell.h"

// Funzione helper per gestire singola redirezione di input
int     handle_input_redir(t_data *data, char *filename)
{
    int fd_file;
    
    fd_file = ft_file(data , filename, 1);
    if (fd_file == -1)
        return (-1);
    dup2(fd_file, STDIN_FILENO);
    close(fd_file);
    return (0);
}

// Funzione helper per gestire singola redirezione di output
int     handle_output_redir(t_data *data, char *filename)
{
    int fd_file;
    
    fd_file = ft_file(data, filename, 2);
    if (fd_file == -1)
        return (-1);
    dup2(fd_file, STDOUT_FILENO);
    close(fd_file);
    return (0);
}

// Funzione helper per gestire singola redirezione di append
int     handle_append_redir(t_data *data, char *filename)
{
    int fd_file;
    
    fd_file = ft_file(data, filename, 3);
    if (fd_file == -1)
        return (-1);
    dup2(fd_file, STDOUT_FILENO);
    close(fd_file);
    return (0);
}

int		handle_heredoc_redir(t_command *cmd)
{
	char *line;
	//int i = 0;

	line = NULL;
	while((line = get_next_line(cmd->heredoc_fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	close(cmd->heredoc_fd);
	return(0);
}