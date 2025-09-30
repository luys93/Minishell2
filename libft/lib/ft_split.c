/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariaber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 10:49:41 by mariaber          #+#    #+#             */
/*   Updated: 2024/12/19 13:07:00 by mariaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_word(const char *s, char c)
{
	size_t	count;

	count = 0;
	while (*s != '\0')
	{
		if (*s != c)
		{
			count++;
			while (*s != c && *s != '\0')
			{
				s++;
			}
		}
		else
			s++;
	}
	return (count);
}

char	**ft_split(char const *s, char c)
{
	char	**phrase;
	size_t	i;
	size_t	len;

	i = 0;
	phrase = (char **)malloc(sizeof(char *) * (count_word(s, c) + 1));
	if (!phrase)
		return (0);
	while (*s != '\0')
	{
		if (*s != c)
		{
			len = 0;
			while (*s != c && *s != '\0')
			{
				len++;
				s++;
			}
			phrase[i++] = ft_substr(s - len, 0, len);
		}
		else
			s++;
	}
	phrase[i] = 0;
	return (phrase);
}
/*int main (int argc, char **argv)
{
	int	p;
	char	**strr;
	p = 0;
	strr = ft_split(argv[1], ' ');
	while (strr[p])
	{
		printf("%s\n", strr[p]);
		p++;
	}
	return(0);
}*/
