/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariaber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 11:58:00 by mariaber          #+#    #+#             */
/*   Updated: 2024/12/26 17:36:49 by mariaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*d;
	char	*s;

	if (!dest && !src)
		return (NULL);
	d = (char *)dest;
	s = (char *)src;
	if (dest <= src)
		return (ft_memcpy(dest, src, n));
	else if (dest > src)
	{
		d += n - 1;
		s += n - 1;
		while (n --)
		{
			*d-- = *s--;
		}
	}
	return (dest);
}
