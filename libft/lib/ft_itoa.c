/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariaber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 14:51:45 by mariaber          #+#    #+#             */
/*   Updated: 2024/12/23 16:05:29 by mariaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	count_nbr(long n)
{
	int	count;

	count = 0;
	if (n <= 0)
	{
		count++;
		if (n < 0)
			n *= -1;
	}
	while (n != 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}

char	*str_malloc(int len)
{
	char	*d;

	d = (char *)malloc(sizeof(char) * (len + 1));
	if (!d)
		return (NULL);
	return (d);
}

char	*ft_itoa(int n)
{
	int		len;
	long	nbr;
	int		i;
	char	*dest;

	nbr = n;
	len = count_nbr(nbr);
	dest = str_malloc(len);
	if (!dest)
		return (NULL);
	dest[len] = '\0';
	if (nbr < 0)
	{
		dest[0] = '-';
		nbr *= -1;
	}
	i = len - 1;
	while (nbr != 0)
	{
		dest[i--] = (nbr % 10) + '0';
		nbr /= 10;
	}
	if (n == 0)
		dest[0] = '0';
	return (dest);
}
/*int main()
{
	int	n = 6788;
	printf("risultato: %s\n", ft_itoa(n));
	return (0);
}*/
