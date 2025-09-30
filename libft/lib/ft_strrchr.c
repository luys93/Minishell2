/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariaber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 12:36:51 by mariaber          #+#    #+#             */
/*   Updated: 2024/12/27 12:49:15 by mariaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;

	i = ft_strlen(s);
	if (c == '\0')
		return ((char *)&s[i]);
	while (i > 0)
	{
		i--;
		if (s[i] == (char)c)
			return ((char *)&s[i]);
	}
	return (NULL);
}

/*int main()
{
	char a[] = "abcs";

	char* result = ft_strrchr(a, 's');
	if (result)
	{
		printf("ultima posizione: %ld\n", result - a);
		printf("resto della stringa: %s\n", result);
	}
	else
		printf("carattere non trovato \n");
	return (0);
}*/
