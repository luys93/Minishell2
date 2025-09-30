/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluciani <lluciani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 17:25:55 by lluciani          #+#    #+#             */
/*   Updated: 2025/07/31 17:25:56 by lluciani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* libera la lista di tutti i comandi */
void	free_all_cmd(t_command *cmd)
{
	int			i;
	t_command	*temp;

	while (cmd)
	{
		temp = cmd->next;
		if (cmd->argv)
		{
			i = 0;
			while (cmd->argv[i])
			{
				safe_free(cmd->argv[i]);
				i++;
			}
			safe_free(cmd->argv);
		}
		free(cmd->path);
		if (cmd->rediraction)
		{
			free_rediraction(cmd->rediraction);
			cmd->rediraction = NULL;
		}
		free(cmd);
		cmd = temp;
	}
}

/* libera la lista di tutti i token */
void	free_all_token(t_token *token)
{
	t_token	*temp;

	while (token)
	{
		temp = token->next;
		if (token->value)
			free(token->value);
		free(token);
		token = temp;
	}
}

void	free_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		free(env[i++]);
	free(env);
}

void	free_rediraction(t_dir *dir)
{
	t_dir	*temp;

	while (dir)
	{
		temp = dir->next;
		if (dir->type)
		{
			safe_free(dir->type);
			dir->type = NULL;
		}
		if (dir->file)
		{
			safe_free(dir->file);
			dir->file = NULL;
		}
		if (dir)
		{
			safe_free(dir);
			dir = NULL;
		}
		dir = temp;
	}
}

/*  se la flag che gli inviamo è uguale a 'v' vuol dire che 
	dobbiamo liberare anche le variabili d'ambiente */
void	free_all(t_data *data, char flag)
{
	if (flag == 'v')
		free_env(data->env);
	if (data->prompt)
	{
		free(data->prompt);
		data->prompt = NULL;
	}
	if (data->command)
	{
		free_all_cmd(data->command);
		data->command = NULL;
	}
	if (data->tokens)
	{
		free_all_token(data->tokens);
		data->tokens = NULL;
	}
	if (data->input)
	{
		free(data->input);
		data->input = NULL;
	}
}
