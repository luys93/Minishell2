/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rediraction.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluciani <lluciani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 17:40:16 by lluciani          #+#    #+#             */
/*   Updated: 2025/07/31 17:40:17 by lluciani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_dir	*add_redirection(t_command *cmd, char *type, char *file)
{
	t_dir	*new;
	t_dir	*temp;

	new = ft_calloc(sizeof(t_dir), 1);
	if (!new)
		return (NULL);
	new->type = ft_strdup(type);
	new->file = ft_strdup(file);
	if (!cmd->rediraction)
	{
		cmd->rediraction = new;
		return (new);
	}
	temp = cmd->rediraction;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
	return (new);
}

void	print_redir(t_command *cmd)
{
	//int			i;
	t_command	*current;
	t_dir		*redir;

	current = cmd;
	redir = NULL;
	//i = 0;
	while (current)
	{
		redir = current->rediraction;
		while (redir)
		{
			printf("Type: %s\n", redir->type);
			printf("File: %s\n", redir->file);
			redir = redir->next;
		}
		current = current->next;
	}
}
