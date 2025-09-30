/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluciani <lluciani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 17:44:56 by lluciani          #+#    #+#             */
/*   Updated: 2025/07/31 18:40:21 by lluciani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*handle_redir_out_and_append(t_command **cmd, t_token *tokens,
		t_command **head, t_command **tail)
{
	if (tokens->type == R_OUT)
	{
		inizialize(cmd, head, tail);
		tokens = parse_r_out(cmd, tokens);
	}
	else if (tokens->type == APPEND)
	{
		inizialize(cmd, head, tail);
		tokens = parse_append(cmd, tokens);
	}
	return (tokens);
}

t_token	*handle_redir_in_and_heredoc(t_command **cmd, t_token *tokens,
		t_command **head, t_command **tail)
{
	if (tokens->type == R_IN)
	{
		inizialize(cmd, head, tail);
		tokens = parse_r_in(cmd, tokens);
	}
	else if (tokens->type == HERE_DOC)
	{
		inizialize(cmd, head, tail);
		tokens = parse_here_doc(cmd, tokens);
	}
	return (tokens);
}

/* questa funzione crea un nuovo comando nella lista dei comandi */
t_token	*parse_cmd(t_command **cmd, t_command **head, t_command **tail,
		t_token *token)
{
	t_command	*new;

	new = init_command();
	if (*head == NULL)
		*head = new;
	else
		(*tail)->next = new;
	*tail = new;
	*cmd = new;
	add_arg(new, token->value);
	return (token->next);
}

/*	qui invece costruiamo la nostra lista,
		ognuna contenente i dettagli di un comando */
t_command	*parser(t_data *data, t_command **head, t_command **tail,
		t_token *tokens)
{
	t_command	*cmd;

	cmd = data->command;
	while (tokens)
	{
		if (tokens->subtype & (CMD | ARG))
			tokens = handle_cmd_and_arg(&cmd, tokens, head, tail);
		else if (tokens->type & (R_OUT | APPEND))
		{
			tokens = handle_redir_out_and_append(&cmd, tokens, head, tail);
			if (!tokens)
				break ;
		}
		else if (tokens->type & (R_IN | HERE_DOC))
		{
			tokens = handle_redir_in_and_heredoc(&cmd, tokens, head, tail);
			if (!tokens)
				break ;
		}
		else
			tokens = tokens->next;
	}
	data->command = *head;
	return (cmd);
}

/* 	qui abbiamo l'inizio del parser
	controlliamo il valore e quello precedente, cosi da capire
	cosa assegnare ai vari token*/
void	parsing(t_data *data)
{
	t_token	*prev;
	t_token	*current;

	prev = NULL;
	current = data->tokens;
	while (current)
	{
		if (parse_condition(current, prev) == CMD)
			current->subtype = CMD;
		else if (parse_condition(current, prev) == FILENAME)
			current->subtype = FILENAME;
		else if (parse_condition(current, prev) == LIMITER)
			current->subtype = LIMITER;
		else if (parse_condition(current, prev) == ARG)
			current->subtype = ARG;
		else if (parse_condition(current, prev) == REDIRECT)
			current->subtype = REDIRECT;
		else
			current->subtype = NONE;
		prev = current;
		current = current->next;
	}
}
