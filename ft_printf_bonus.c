/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mny-aro- <mny-aro-@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 10:00:00 by mny-aro-          #+#    #+#             */
/*   Updated: 2026/03/26 18:15:16 by mny-aro-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

static int	parse_and_print(const char *format, int i, va_list args, int *count)
{
	t_fmt	fmt;

	fmt_init(&fmt);
	i = parse_flags(format, i + 1, &fmt);
	if (!format[i])
		return (-1);
	*count += handle_conversion(args, &fmt);
	return (i + 1);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		count;
	int		i;

	if (!format)
		return (-1);
	va_start(args, format);
	count = 0;
	i = 0;
	while (format[i])
	{
		if (format[i] != '%')
			count += ft_putchar(format[i++]);
		else
		{
			i = parse_and_print(format, i, args, &count);
			if (i == -1)
				break ;
		}
	}
	va_end(args);
	return (count);
}
