/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluciani <lluciani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 17:30:14 by lluciani          #+#    #+#             */
/*   Updated: 2025/07/31 17:33:17 by lluciani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*exit_status(t_data *data, char *str, char *pre_value, int *i)
{
	char	*temp;
	char	*result;

	temp = NULL;
	result = NULL;
	if (str[*i] == '$' && str[*i + 1] == '?')
	{
		temp = ft_itoa(data->exit_status);
		*i += 2;
		result = safe_strjoin(pre_value, temp);
		free(temp);
	}
	return (result);
}

char	*no_expansion(char *str)
{
	char	*temp;

	temp = ft_strdup(str);
	if (str)
		safe_free(str);
	return (temp);
}

char	*reset_value(char **str, char *result, int flag)
{
	safe_free(*str);
	if(result == NULL && flag == 0)
	{
		*str = NULL;
		free(result);
		return(NULL);

	}
	else if(ft_strcmp(result, "") == 0 && flag == 2)
	{
		*str = ft_strdup("");
		free(result);
		return(NULL);
	}
	*str = ft_strdup(result);
	free(result);
	return (NULL);
}

char *handle_empty_str(t_token *prev, t_token *current, char *result)
{

	//if((!prev || (prev && !prev->value)) && ft_strcmp(result, NULL) == 0)
	if((!prev && !result) || (prev && !result))
	{
		result = reset_value(&current->value, result, 0);
	}
	else if ((!prev || (prev && !prev->value)) && ft_strcmp(result, "") == 0)
	{
		result = reset_value(&current->value, result, 2);
	}
	else
	{
		result = reset_value(&current->value, result, 1);
	}
	return(result);
}