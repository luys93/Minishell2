/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluciani <lluciani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 17:29:17 by lluciani          #+#    #+#             */
/*   Updated: 2025/07/31 17:29:18 by lluciani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*replace_value(t_data *data, char *str, int *pos)
{
	char	*word;
	char	*value;

	word = NULL;
	value = NULL;
	word = extract_word(str, pos);
	if (word[0] == '\0')
	{
		free(word);
		return (str);
	}
	value = get_env(word);
	if(!value)
		value = get_env_value(data->env, word);
	free(word);
	if (value == NULL)
		return (NULL);
	return (ft_strdup(value));
}

char	*extract_word(char *str, int *pos)
{
	int		i;
	int		j;
	char	*word;

	i = *pos;
	j = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1])
		{
			i++;
			break ;
		}
		i++;
	}
	j = i;
	while (str[j] && is_valid(str[j]))
		j++;
	word = ft_strndup(&str[i], (j - i));
	*pos = j;
	return (word);
}

char	*get_env(char *str)
{
	char	*value;

	value = getenv(str);
	if (!value)
		return (NULL);
	return (value);
}

int	is_valid(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (1);
	else
		return (0);
}

char	*ft_strcpy_mod(char *str, int *pos)
{
	int		i;
	int		j;
	char	*word;

	i = 0;
	j = 0;
	word = ft_calloc(sizeof(char), (ft_strlen(str) + 1));
	if (!word)
		return (NULL);
	i = *pos;
	while (str[i] && str[i] != '$')
	{
		word[j] = str[i];
		i++;
		j++;
	}
	word[j] = '\0';
	*pos = i;
	return (word);
}
