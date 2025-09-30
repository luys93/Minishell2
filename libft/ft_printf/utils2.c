/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariaber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 14:17:08 by mariaber          #+#    #+#             */
/*   Updated: 2025/01/21 10:22:02 by mariaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// stampa i numeri in base sedici
void	ft_puthex(unsigned int num, int *count, const char c)
{
	if (num == 0)
	{
		ft_putchar('0', count);
		return ;
	}
	else if (num >= 16)
	{
		ft_puthex(num / 16, count, c);
		ft_puthex(num % 16, count, c);
	}
	else
	{
		if (num <= 9)
		{
			ft_putchar((num + '0'), count);
		}
		else
		{
			if (c == 'x')
				ft_putchar((num - 10 + 'a'), count);
			if (c == 'X')
				ft_putchar((num - 10 + 'A'), count);
		}
	}
}

// stampa la prima parte del puntatore
void	ft_putpntr(void *num, int *count)
{
	unsigned long long	n;

	if (!num)
	{
		ft_putstr("(nil)", count);
		return ;
	}
	n = (unsigned long long)num;
	ft_putstr("0x", count);
	ft_puthexp(n, count);
}

// stampa il numero del puntatore
void	ft_puthexp(unsigned long long num, int *count)
{
	if (num == 0)
	{
		ft_putchar('0', count);
		return ;
	}
	else if (num >= 16)
	{
		ft_puthexp(num / 16, count);
		ft_puthexp(num % 16, count);
	}
	else
	{
		if (num <= 9)
		{
			ft_putchar((num + '0'), count);
		}
		else
		{
			ft_putchar((num - 10 + 'a'), count);
		}
	}
}
