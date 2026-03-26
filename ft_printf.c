/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mny-aro- <mny-aro-@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 08:59:10 by mny-aro-          #+#    #+#             */
/*   Updated: 2026/03/02 15:54:41 by mny-aro-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_check_format(char spec, va_list args)
{
	int	count;

	count = 0;
	if (spec == 'c')
		count += ft_putchar(va_arg(args, int));
	else if (spec == 's')
		count += ft_putstr(va_arg(args, char *));
	else if (spec == 'p')
		count += ft_putptr(va_arg(args, void *));
	else if (spec == 'd' || spec == 'i')
		count += ft_putnbr(va_arg(args, int));
	else if (spec == 'u')
		count += ft_putnbr_unsigned(va_arg(args, unsigned int));
	else if (spec == 'x')
		count += ft_putnbr_hex(va_arg(args, unsigned int), 'x');
	else if (spec == 'X')
		count += ft_putnbr_hex(va_arg(args, unsigned int), 'X');
	else if (spec == '%')
		count += ft_putchar('%');
	else
	{
		count += ft_putchar('%');
		count += ft_putchar(spec);
	}
	return (count);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		count;
	int		i;

	i = 0;
	count = 0;
	if (!format)
		return (-1);
	va_start(args, format);
	while (format[i])
	{
		if (format[i] == '%')
		{
			i += 1;
			count += ft_check_format(format[i], args);
		}
		else
		{
			ft_putchar(format[i]);
			count += 1;
		}
		i++;
	}
	va_end(args);
	return (count);
}
