/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluciani <lluciani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 17:26:08 by lluciani          #+#    #+#             */
/*   Updated: 2025/07/31 17:37:06 by lluciani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	*joining_token(t_token *tokens);
static int		check_type(int type);

/*	questa funzione ha il compito di concatenare diversi token assieme
	quando neccesario grazie alla flag "must_joined" e ad altri check*/
void	joined_token(t_token *token)
{
	t_token	*current;
	//char	*joined;

	current = token;
	//joined = current->value;
	while (current)
	{
		while ((current->must_joined == 1 && current->next)
			&& (check_type(current->next->type) == 0))
		{
			if (current->next->must_joined == 0)
			{
				current->next = joining_token(current);
				if (current->next)
				{
					current = current->next;
					continue ;
				}
				return ;
			}
			current->next = joining_token(current);
		}
		current = current->next;
	}
	return ;
}

t_token	*joining_token(t_token *tokens)
{
	t_token	*new;

	tokens->value = safe_strjoin(tokens->value, tokens->next->value);
	new = tokens->next;
	tokens->next = new->next;
	free(new->value);
	free(new);
	return (tokens->next);
}

/* quando incontra un metachar gli assegna subito il tipo */
void	add_type(t_data *data)
{
	t_token	*current;

	current = data->tokens;
	while (current)
	{
		if (ft_strcmp(current->value, ">>") == 0)
			current->type = APPEND;
		else if (ft_strcmp(current->value, "<<") == 0)
			current->type = HERE_DOC;
		else if (ft_strcmp(current->value, "|") == 0)
			current->type = PIPE;
		else if (ft_strcmp(current->value, "<") == 0)
			current->type = R_IN;
		else if (ft_strcmp(current->value, ">") == 0)
			current->type = R_OUT;
		current = current->next;
	}
}

static int	check_type(int type)
{
	if (type == R_OUT)
		return (1);
	if (type == R_IN)
		return (1);
	if (type == APPEND)
		return (1);
	if (type == HERE_DOC)
		return (1);
	if (type == PIPE)
		return (1);
	return (0);
}
