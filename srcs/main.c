/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluciani <lluciani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 17:25:25 by lluciani          #+#    #+#             */
/*   Updated: 2025/09/27 15:56:16 by lluciani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	input_execution(t_data *data);

int			g_status_signal;

int	main(void)
{
	t_data	data;
	//char	*prompt;
	int		status;

	ft_memset(&data, 0, sizeof(t_data)); //non si puo usare memset
	init_env(&data);
	signal_handler(SIGINT, sigint_handler);
	while (1)
	{
		data.prompt = ft_getprompt();
		status = read_line(&data);
		if (g_status_signal == SIGINT)
			data.exit_status = 130;
		else if (g_status_signal == SIGQUIT)
			data.exit_status = 131;
		if (status == 1)
		{
			free_all(&data, 'v');
			ft_printf("exit\n");
			return (0);
		}
		else if (status == 2)
		{
			free_all(&data, 'x');
			continue ;
		}
		if (input_execution(&data) == 1) // usiamo il free input_execution, no problem
			continue ;
		free_all(&data, 'x');
	}
}

/* funzione di esecuzione dell'input */
static int	input_execution(t_data *data)
{
	if (handle_input(data) == 0)
	{
		ft_execution(data, data->command);
		return (0);
	}
	//data->exit_status = 2;
	free_all(data, 'x');
	return (1);
}

/* x testare 
    valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=supp.supp ./minishell*/




/* problema con ft_file su input:        ./test_files     perchè restituisce un codice 127 e un command not found */

/* vedere come fa il controllo se è un comando o una directory, perchè spesso vengono confuse */

/* altro problema con questo input:    cat come.h | grep ""     */