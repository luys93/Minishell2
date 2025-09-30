/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluciani <lluciani@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 23:15:51 by lluciani          #+#    #+#             */
/*   Updated: 2025/08/08 23:15:55 by lluciani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void change_subtype(t_token *tokens);

t_token	*handle_cmd_and_arg(t_command **cmd, t_token *tokens, t_command **head,
		t_command **tail)
{
	if (tokens->subtype == CMD)
	{
		if(!tokens->value)
		{
			change_subtype(tokens);
			return(tokens->next);
		}
		tokens = parse_cmd(cmd, head, tail, tokens);
	}
	else if (tokens->subtype == ARG)
		tokens = parse_arg(cmd, tokens);
	return (tokens);
}


static void change_subtype(t_token *tokens)
{
	while(tokens->next)
	{
		if(!tokens->value && tokens->subtype == CMD)
		{
			if(tokens->next->subtype == ARG)
				tokens->next->subtype = CMD;	
		}
		tokens = tokens->next;
	}
	return;
}