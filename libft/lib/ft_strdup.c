/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariaber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 11:28:11 by mariaber          #+#    #+#             */
/*   Updated: 2024/12/27 10:36:56 by mariaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	int		len;
	char	*dest;

	len = ft_strlen(s);
	dest = (char *)malloc(sizeof(char) * len + 1);
	if (!dest)
		return (NULL);
	ft_strlcpy(dest, (char *)s, len + 1);
	return (dest);
}
/*int main(int ac, char **av)
{
	printf("primo argomento %s\n",av[1]);
	char *str = ft_strdup(av[1]);
	printf("argomento copiato %s\n", str);
}*/
