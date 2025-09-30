/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluciani <lluciani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 17:25:14 by lluciani          #+#    #+#             */
/*   Updated: 2025/07/31 17:28:46 by lluciani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*int	rediraction_error(t_command *command)
{
	t_command	*cmd;
	t_dir		*redir;

	redir = NULL;
	cmd = command;
	while (cmd)
	{
		redir = cmd->rediraction;
		while (redir)
		{
			if (ft_strlen(redir->file) == 0 && 
				ft_strcmp(redir->type, "<<") != 0)
				return (1);
			redir = redir->next;
		}
		cmd = cmd->next;
	}
	return (0);
}*/

int	split_word_error(int *pos, t_data *data, int i)
{
	if (!data->input[i])
	{
		write(2, "Error, missing closing quotes\n", 30);
		*pos = i;
		return (1);
	}
	return (0);
}

int	rediraction_error(t_data *data, t_command *command)
{
	t_command	*cmd;
	t_dir		*redir;

	redir = NULL;
	cmd = command;
	while (cmd)
	{
		redir = cmd->rediraction;
		while (redir)
		{
			if(redir && strcmp(redir->file, "none") == 0)
			{
				data->exit_status = 258;
				return(1);
			}
			if (ft_strlen(redir->file) == 0 && 
				ft_strcmp(redir->type, "<<") != 0)
				return (1);
			redir = redir->next;
		}
		cmd = cmd->next;
	}
	return (0);
}
