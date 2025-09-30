/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariaber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 10:04:49 by mariaber          #+#    #+#             */
/*   Updated: 2025/01/22 10:33:40 by mariaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// funzione di controllo, per i numeri interi
void	ft_check(int n, int *count)
{
	if (n == 0 || n == -2147483648)
		ft_checkzero(n, count);
	else if (n < 0)
	{
		ft_putchar('-', count);
		ft_putnbr((unsigned int)(-n), count);
	}
	else
		ft_putnbr((unsigned int)n, count);
}

// stampa zero e min int
void	ft_checkzero(int n, int *count)
{
	if (n == 0)
	{
		ft_putchar('0', count);
	}
	else
	{
		ft_putstr("-2147483648", count);
	}
}

// stampa i numeri trasformandoli in una stringa
void	ft_putnbr(unsigned int n, int *count)
{
	int		i;
	char	*num;

	i = ft_countnum(n);
	num = (char *)malloc(i + 1);
	if (!num)
		return ;
	num[i] = '\0';
	if (n == 0)
	{
		num[0] = '0';
	}
	while (n != 0)
	{
		num[i - 1] = (n % 10) + 48;
		n /= 10;
		i--;
	}
	ft_putstr(num, count);
	free(num);
}

// serve per putnbr, conta quanti numeri(spazio) devo allocare nella stringa
int	ft_countnum(unsigned int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		i++;
		n /= 10;
	}
	return (i);
}
