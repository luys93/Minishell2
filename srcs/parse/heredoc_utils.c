/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluciani <lluciani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 17:41:22 by lluciani          #+#    #+#             */
/*   Updated: 2025/07/31 17:41:57 by lluciani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*is_h_delimiter(t_token *tokens)
{
	t_token	*current;
	char	*delimiter;

	delimiter = NULL;
	current = tokens;
	while (current)
	{
		if (current->subtype == LIMITER)
			delimiter = current->value;
		current = current->next;
	}
	return (delimiter);
}

int	is_expansion(t_token *tokens)
{
	while (tokens)
	{
		//printf("valore e:%s\n", tokens->value);
		if (tokens->subtype == LIMITER && !tokens->quote_type)
		{
			//printf("le quote:%c\n", tokens->quote_type);
			return (1);
		}
		tokens = tokens->next;
	}
	return (0);
}

int	fd_error(int fd, char *filename)
{
	if (fd == -1)
	{
		write(2, "ERROR: invalid open fd\n", 24);
		safe_free(filename);
		return (1);
	}
	return (0);
}

int	here_doc_condition(t_command *command)
{
	t_dir	*redir;

	while (command)
	{
		redir = command->rediraction;
		while (redir)
		{
			if (ft_strcmp(redir->type, "<<") == 0)
			{
				return (1);
			}
			redir = redir->next;
		}
		command = command->next;
	}
	return (0);
}
