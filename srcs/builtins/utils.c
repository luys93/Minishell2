#include "minishell.h"

// non credo serva.. (non si sa mai)
int     ft_count_token(t_token *tokens)
{
    int         count;
    t_token     *curr;

    count = 0;
    curr = tokens;
    while (curr)
    {
        count++;
        curr = curr->next;
    }
    return(count);
}

// conta gli argomenti di un comando passatogli
int     ft_count_argument(t_command *cmd)
{
	int i;

	i = 0;
    if (!cmd | !cmd->argv)
        return(0);
    while (cmd->argv[i] != NULL)
		i++;
    return(i);
}