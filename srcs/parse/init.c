/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluciani <lluciani@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 16:10:57 by lluciani          #+#    #+#             */
/*   Updated: 2025/08/08 16:11:47 by lluciani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	inizialize(t_command **cmd, t_command **head, t_command **tail)
{
	t_command	*new;

	if (*cmd == NULL)
	{
		new = init_command();
		if (*head == NULL)
		{
			*head = new;
		}
		else
			(*tail)->next = new;
		*tail = new;
		*cmd = new;
	}
}

/* init dei comandi */
t_command	*init_command(void)
{
	t_command	*cmd;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->argv = NULL;
	cmd->path = NULL;
	cmd->rediraction = NULL;
	cmd->heredoc_fd = 0;
	cmd->append = 0;
	cmd->next = NULL;
	return (cmd);
}

/* init variabili d'ambiente */
void	init_env(t_data *data)
{
	extern char	**environ;
	int			count;
	int			i;

	i = 0;
	count = 0;
	while (environ[count] != NULL)
		count++;
	data->env = malloc((count + 1) * sizeof(char *));
	while (i < count)
	{
		data->env[i] = ft_strdup(environ[i]);
		i++;
	}
	data->env[i] = NULL;
}
