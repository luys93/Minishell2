/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluciani <lluciani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 17:25:18 by lluciani          #+#    #+#             */
/*   Updated: 2025/07/31 17:25:19 by lluciani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_input(t_data *data)
{
	t_command	*head;
	t_command	*tail;
	t_command *cmd;
	

	head = NULL;
	tail = NULL;
	if (tokenizer(data) == 1)
		return (1);
	add_type(data);
	parsing(data);
	if (error_pipe(data) == 0)
		return (1);
	check_expansion(data, data->tokens);
	joined_token(data->tokens);
	cmd = parser(data, &head, &tail, data->tokens);
	/*if(cmd->rediraction && strcmp(cmd->rediraction->file, "none") == 0)
	{
		data->exit_status = 258;
		return(1);
	}*/
	if(rediraction_error(data, cmd) == 1)
		return(1);
	if (here_doc_condition(data->command) == 1)
		 here_doc(data, data->tokens, data->command);
	data->command = head;
	/*if (rediraction_error(data->command) == 1)
		return (1);*/
	return (0);
}

/* controllo sulla stringa */
int	control_string(t_data *data)
{
	size_t	i;

	i = 0;
	while (is_space(data->input[i]))
	{
		i++;
	}
	if (data->input[i] == '\0')
		return (1);
	else
		return (0);
}

/* controlla l'input */
int	check_input(t_data *data)
{
	if (!data->input)
	{
		return (1);
	}
	else if (data->input[0] == '\0' || control_string(data) == 1)
		return (2);
	return (0);
}

/* funzione che controlla il ctrl+C e ctrl+D */
int	read_line(t_data *data)
{
	data->input = readline(data->prompt);
	if (check_input(data) == 1)
		return (1);
	if (*data->input)
	{
		add_history(data->input);
	}
	if (check_input(data) == 2)
		return (2);
	return (0);
}

