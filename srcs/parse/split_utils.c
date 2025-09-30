/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluciani <lluciani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 17:40:48 by lluciani          #+#    #+#             */
/*   Updated: 2025/07/31 17:41:04 by lluciani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_space(char c)
{
	return (c == ' ' || c == '\t');
}

int	is_quotes(char c)
{
	return (c == '\'');
}

int	is_double_quotes(char c)
{
	return (c == '"');
}

int	is_delimiter(char c)
{
	return (c == '<' || c == '>' || c == '|');
}

int	is_match(char *s)
{
	if (s[0] == '<' && s[1] == '<')
		return (2);
	if (s[0] == '>' && s[1] == '>')
		return (2);
	if (s[0] == '<')
		return (1);
	if (s[0] == '>')
		return (1);
	if (s[0] == '|')
		return (1);
	return (0);
}
