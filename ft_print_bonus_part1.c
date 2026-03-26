/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_bonus_part1.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mny-aro- <mny-aro-@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 18:20:00 by mny-aro-          #+#    #+#             */
/*   Updated: 2026/03/26 18:17:17 by mny-aro-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

int	print_char_bonus(char c, t_fmt *fmt)
{
	int	count;

	count = 0;
	if (!fmt->flag_minus)
		count += put_nchar(' ', fmt->width - 1);
	count += ft_putchar(c);
	if (fmt->flag_minus)
		count += put_nchar(' ', fmt->width - 1);
	return (count);
}

int	print_string_bonus(char *s, t_fmt *fmt)
{
	int	count;
	int	len;

	if (!s)
		s = "(null)";
	len = (int)ft_strlen_bonus(s);
	if (fmt->flag_dot && fmt->precision < len)
		len = fmt->precision;
	count = 0;
	if (!fmt->flag_minus)
		count += put_nchar(' ', fmt->width - len);
	count += putstr_n(s, len);
	if (fmt->flag_minus)
		count += put_nchar(' ', fmt->width - len);
	return (count);
}

int	print_percent_bonus(t_fmt *fmt)
{
	int		count;
	char	pad;

	count = 0;
	pad = ' ';
	if (fmt->flag_zero && !fmt->flag_minus)
		pad = '0';
	if (!fmt->flag_minus)
		count += put_nchar(pad, fmt->width - 1);
	count += ft_putchar('%');
	if (fmt->flag_minus)
		count += put_nchar(' ', fmt->width - 1);
	return (count);
}
