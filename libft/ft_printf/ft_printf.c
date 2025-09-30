/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariaber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 11:17:09 by mariaber          #+#    #+#             */
/*   Updated: 2025/01/22 10:30:05 by mariaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		count;

	count = 0;
	va_start(args, str);
	while (*str)
	{
		if (*str == '%')
		{
			str++;
			ft_print_format(*str, args, &count);
		}
		else
		{
			ft_putchar(*str, &count);
		}
		str++;
	}
	va_end(args);
	return (count);
}

void	ft_print_format(const char c, va_list args, int *count)
{
	if (c == 'c')
		ft_putchar(va_arg(args, int), count);
	if (c == 's')
		ft_putstr(va_arg(args, char *), count);
	if (c == 'p')
		ft_putpntr(va_arg(args, void *), count);
	if (c == 'd' || c == 'i')
		ft_check(va_arg(args, int), count);
	if (c == 'u')
		ft_putnbr(va_arg(args, unsigned int), count);
	if (c == 'x' || c == 'X')
		ft_puthex(va_arg(args, unsigned int), count, c);
	if (c == '%')
		ft_putchar('%', count);
}

// stampa carattere
void	ft_putchar(char c, int *count)
{
	write(1, &c, 1);
	(*count)++;
}

// stampa la stringa richiamando putchar
void	ft_putstr(char *str, int *count)
{
	if (!str)
	{
		ft_putstr("(null)", count);
		return ;
	}
	while (*str)
	{
		ft_putchar(*str, count);
		str++;
	}
}
