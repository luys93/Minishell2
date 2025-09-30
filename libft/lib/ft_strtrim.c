/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariaber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 09:51:06 by mariaber          #+#    #+#             */
/*   Updated: 2024/12/27 12:01:04 by mariaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s, char const *set)
{
	int		start;
	int		end;
	char	*trimmed;

	start = 0;
	if (!s || !set)
		return (NULL);
	end = ft_strlen(s);
	trimmed = (char *)malloc(sizeof(char) * (end + 1));
	if (!trimmed)
		return (NULL);
	while (ft_strchr(set, s[start]) && s[start])
		start++;
	while (ft_strchr(set, s[end - 1]) && end > start)
		end--;
	trimmed = ft_substr(s, start, end - start);
	return (trimmed);
}

/*int main()
{
	char	a[] = "ciao***";
	char	b[] = "*i";
	printf("risultato: %s\n", ft_strtrim(a, b));
	return (0);
}*/
