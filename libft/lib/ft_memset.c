/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariaber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 12:20:26 by mariaber          #+#    #+#             */
/*   Updated: 2025/01/07 14:16:45 by mariaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*buffer;

	if (!s)
		return (NULL);
	buffer = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		buffer[i] = (unsigned char)c;
		i++;
	}
	return (s);
}
