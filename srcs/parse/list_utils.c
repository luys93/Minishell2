/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluciani <lluciani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 17:25:43 by lluciani          #+#    #+#             */
/*   Updated: 2025/07/31 17:25:44 by lluciani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_arg(t_command *cmd, char *value)
{
	int		count;
	int		i;
	char	**new_arg;

	count = 0;
	i = 0;
	if (cmd->argv)
	{
		while (cmd->argv[count])
		{
			count++;
		}
	}
	new_arg = malloc(sizeof(char *) * (count + 2));
	if (!new_arg)
		return ;
	while (i < count)
	{
		new_arg[i] = cmd->argv[i];
		i++;
	}
	new_arg[count] = ft_strdup(value);
	new_arg[count + 1] = NULL;
	free(cmd->argv);
	cmd->argv = new_arg;
}

/*	aggiungiamo alla lista il token, mettendo il valore, il tipo e quote_type,
		per riconoscere
	quale quote bisogna prendere in considerazione, il resto mettiamo a NULL*/
t_token	*add_token_to_list(t_data *data, char *value, token_type type,
		char quote_type)
{
	t_token	*new;
	t_token	*temp;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->value = ft_strdup(value);
	new->type = type;
	new->quote_type = quote_type;
	new->subtype = NONE;
	new->next = NULL;
	new->must_joined = 0;
	free(value);
	if (!data->tokens)
	{
		data->tokens = new;
		return (new);
	}
	temp = data->tokens;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
	return (new);
}
