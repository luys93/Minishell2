/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluciani <lluciani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 17:25:04 by lluciani          #+#    #+#             */
/*   Updated: 2025/07/31 17:44:30 by lluciani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	safe_free(void *ptr)
{
	free(ptr);
	ptr = NULL;
}

char	*safe_strjoin(char *s1, char *s2)
{
	char	*word;

	word = NULL;
	if (!s1)
	{
		s1 = ft_calloc(sizeof(char), 1);
		if (!s1)
			return (NULL);
	}
	word = ft_strjoin(s1, s2);
	free(s1);
	s1 = NULL;
	return (word);
}

/* libera un array*/
void	ft_free_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
}

int	error_pipe(t_data *data)
{
	t_token	*current;

	current = data->tokens;
	while (current)
	{
		if (current->type == PIPE && !current->next)
		{
			write(2, "syntax error: near unexpected token `|'\n", 40);
			data->exit_status = 258;
			return (0);
		}
		current = current->next;
	}
	return (1);
}

char *get_env_value(char **env, const char *var)
{
	int i = 0;
	int len = ft_strlen(var);
	while(env[i])
	{
		if(ft_strncmp(env[i],var, len) == 0 && env[i][len] == '=')
			return(env[i] + len + 1);
		i++;
	}
	return(NULL);
}