/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluciani <lluciani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 17:26:04 by lluciani          #+#    #+#             */
/*   Updated: 2025/07/31 17:26:05 by lluciani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* aggiunge l'argomento al comando e passa al token successivo */
t_token	*parse_arg(t_command **cmd, t_token *token)
{
	add_arg(*cmd, token->value);
	return (token->next);
}

/* imposta il file di output */
t_token	*parse_r_out(t_command **cmd, t_token *token)
{
	if (token->next)
	{
		if (is_match(token->next->value))
		{
			write(2, "error: double rediraction, not file found\n", 43);
			add_redirection(*cmd, token->value, "none");
			return (NULL);
		}
		add_redirection(*cmd, token->value, token->next->value);
	}
	else
	{
		write(2, "error: syntax error near unexpected token `newline'\n", 53);
		add_redirection(*cmd, token->value, "none");
		return (NULL);
	}
	return (token->next->next);
}

/* stessa cosa di r_out ma imposta append = 1 (>>) */
t_token	*parse_append(t_command **cmd, t_token *token)
{
	if (token->next)
	{
		if (is_match(token->next->value))
		{
			write(2, "error: double rediraction, not file found\n", 43);
			add_redirection(*cmd, token->value, "none");
			return (NULL);
		}
		add_redirection(*cmd, token->value, token->next->value);
		(*cmd)->append = 1;
	}
	else
	{
		write(2, "error: syntax error near unexpected token `newline'\n", 53);
		add_redirection(*cmd, token->value, "none");
		return (NULL);
	}
	return (token->next->next);
}

/* imposta il file di input */
t_token	*parse_r_in(t_command **cmd, t_token *token)
{
	if (token->next)
	{
		if (is_match(token->next->value))
		{
			write(2, "error: double rediraction, not file found\n", 43);
			add_redirection(*cmd, token->value, "none");
			return (NULL);
		}
		add_redirection(*cmd, token->value, token->next->value);
	}
	else
	{
		write(2, "error: syntax error near unexpected token `newline'\n", 53);
		add_redirection(*cmd, token->value, "none");
		return (NULL);
	}
	return (token->next->next);
}

/* salva il delimitatore */
t_token	*parse_here_doc(t_command **cmd, t_token *token)
{
	if (token->next)
	{
		if (is_match(token->next->value))
		{
			write(2, "error: double rediraction, not file found\n", 43);
			add_redirection(*cmd, token->value, "none");
			return (NULL);
		}
		add_redirection(*cmd, token->value, token->next->value);
	}
	else
	{
		write(2, "error: syntax error near unexpected token `newline'\n", 53);
		add_redirection(*cmd, token->value, "none");
		return (NULL);
	}
	return (token->next->next);
}
