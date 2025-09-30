/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluciani <lluciani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 17:25:30 by lluciani          #+#    #+#             */
/*   Updated: 2025/07/31 17:37:56 by lluciani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*is_expanded(t_data *data, char *value, int *i);

void	init_vars(t_token **prev, char **result, char **temp, int *i)
{
	*prev = NULL;
	*result = NULL;
	*temp = NULL;
	*i = 0;
}

/*               ultima prova espansione */

char	*check_expansion(t_data *data, t_token *tokens)
{
	t_token	*current;
	t_token *prev;
	char	*result;
	char	*temp;
	int		i;

	current = tokens;
	init_vars(&prev, &result, &temp, &i);
	while (current)
	{
		i = 0;
		if ((current->quote_type == '\'')
			|| !(current->subtype & (CMD | FILENAME | ARG)))
		{
			current->value = no_expansion(current->value);
			current = current->next;
			continue ;
		}
		if ((current->quote_type == '"' || !current->quote_type))
			result = is_expanded(data, current->value, &i);
		result = handle_empty_str(prev, current, result);
		prev = current;
		current = current->next;
	}
	return (NULL);
}

static char	*is_expanded(t_data *data, char *value, int *i)
{
	char	*result;

	result = expansion_core(data, value, i);
	if(!result)
		return(ft_strdup("")); // cambiato da return(NULL) a return(stringa vuota). Controllare se cambia qualche comportamento importante nel resto del software!
	if (value[0] == '\0')
		result = ft_strdup("");
	return (result);
}

char	*expansion_core(t_data *data, char *str, int *i)
{
	char	*temp;
	char	*result;

	temp = NULL;
	result = NULL;
	while (str[*i])
	{
		temp = ft_strcpy_mod(str, i);
		result = safe_strjoin(result, temp);    
		safe_free(temp);
		if (str[*i] == '$')
			result = allow_expansion(data, str, result, i);
	}
	if(ft_strcmp(str, "") == 0)
		return(ft_strdup(""));
	return (result);
}

char	*allow_expansion(t_data *data, char *str, char *pre_value, int *i)
{
	char	*temp;
	char	*result;

	temp = NULL;
	result = NULL;
	if (is_valid(str[*i + 1]))
	{
		temp = replace_value(data, str, i);
		if(!pre_value && !temp)
			return(NULL);
		result = safe_strjoin(pre_value, temp);
		safe_free(temp);
	}
	else if (str[*i + 1] == '?')
	{
		temp = exit_status(data, str, pre_value, i);
		result = safe_strjoin(result, temp);
		free(temp);
	}
	else
	{
		result = safe_strjoin(pre_value, "$");
		(*i)++;
	}
	return (result);
}
