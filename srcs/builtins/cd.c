#include "minishell.h"

/* controllare argomenti dopo cd, solo 1, con 2 
o piu argomenti "cd: too many arguments"
mentre se non trova il percorso passato perror("cd: [nome percorso]:") */
void    ft_cd(t_data *data, t_command *cmd)
{
    int     arg;
	//int 	count;
	struct stat st;
	char *buffer;
	int i;

	buffer = NULL;
	i = 0;
    arg = ft_count_argument(cmd);
    if (arg == 1 && chdir(getenv("HOME")) == -1)
        perror("Error");
    else if (arg > 2)
        perror("too many arguments");
    else if (cmd->argv[i] &&  stat(data->command->argv[i + 1], &st) != 0) 
			error_process(data, data->command->argv[i + 1], " No such file or directory", 1);
	else
	{
		buffer = getcwd(data->command->path, sizeof(cmd->path));
		if(!buffer)
		{
			perror("getcwd error");
			return;
		}
		if(stat(data->command->argv[i + 1], &st) == 0)
		{
			if(S_ISDIR(st.st_mode))
			{
				char *buffer2 = ft_strjoin(buffer, "/");
				buffer2 = ft_strjoin(buffer2,data->command->argv[i + 1]);
				if(chdir(buffer2) != 0)
					perror("chdir error");
				free(buffer2);		
			}
		}
		else
			error_process(data, data->command->argv[i + 1], ": Not a directory\n", 1);
	}
	safe_free(buffer);
	return ;
}
/* CD da sistemare, per ora gestire solo errori*/