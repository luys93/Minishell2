#include "minishell.h"

static char	*rediraction_type(token_type type);

/* confronta i type e subtype */
int	parse_condition(t_token *token, t_token *prev)
{
	if (token->type & (WORD | QUOTED))
	{
		if (prev == NULL || prev->type == PIPE)
			return (CMD);
		if (prev->type & (R_OUT | APPEND | R_IN))
			return (FILENAME);
		if (prev->type == HERE_DOC)
			return (LIMITER);
		if (prev->subtype & (CMD | ARG) || prev->subtype == FILENAME)
			return (ARG);
	}
	else if ((token->type & (R_OUT | R_IN | APPEND | HERE_DOC)))
		return (REDIRECT);
	return (NONE);
}

/* stampa tutti i valori della lista tokens */
void	print_token(t_token *head)
{
	while (head != NULL)
	{
		printf("value: %s\n", head->value);
		printf("type: %s\n", token_type_str(head->type));
		printf("subtype: %s\n", token_type_str(head->subtype));
		printf("quote type: %c\n", head->quote_type);
		printf("must joined: %d\n", head->must_joined);
		printf("--------------------------\n");
		head = head->next;
	}
}

/* stampa tutti i comandi */
void	print_command_list(t_command *cmd)
{
	int	i;

	while (cmd)
	{
		i = 0;
		if (cmd->argv)
		{
			while (cmd->argv[i])
			{
				printf("il contenuto di argv e:%s\n", cmd->argv[i]);
				i++;
			}
		}
		printf("path del comando:%s\n", cmd->path);
		printf("heredoc_fd e:%d\n", cmd->heredoc_fd);
		printf("append è :%d\n", cmd->append);
		cmd = cmd->next;
	}
}

char	*token_type_str(token_type type)
{
	if (type == NONE)
		return ("NONE");
	else if (type == PIPE)
		return ("PIPE");
	else if (rediraction_type(type))
		return (rediraction_type(type));
	else if (type == CMD)
		return ("CMD");
	else if (type == ARG)
		return ("ARG");
	else if (type == WORD)
		return ("WORD");
	else if (type == QUOTED)
		return ("QUOTED");
	else if (type == METACHAR)
		return ("METACHAR");
	return ("BOH");
}

static char	*rediraction_type(token_type type)
{
	if (type == LIMITER)
		return ("LIMITER");
	else if (type == DELIMITER)
		return ("DELIMITER");
	else if (type == REDIRECT)
		return ("REDIRECT");
	else if (type == FILENAME)
		return ("FILENAME");
	else if (type == HERE_DOC)
		return ("HERE_DOC");
	else if (type == R_IN)
		return ("R_IN");
	else if (type == APPEND)
		return ("APPEND");
	else if (type == R_OUT)
		return ("R_OUT");
	return (NULL);
}
