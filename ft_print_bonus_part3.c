/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_bonus_part3.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mny-aro- <mny-aro-@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 18:20:00 by mny-aro-          #+#    #+#             */
/*   Updated: 2026/03/26 18:26:43 by mny-aro-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

static int	print_null_ptr(t_fmt *fmt)
{
	int	count;

	count = 0;
	if (!fmt->flag_minus)
		count += put_nchar(' ', fmt->width - 5);
	count += putstr_n("(nil)", 5);
	if (fmt->flag_minus)
		count += put_nchar(' ', fmt->width - 5);
	return (count);
}

int	print_pointer_bonus(void *ptr, t_fmt *fmt)
{
	uintptr_t	num;
	int			count;
	int			digits;
	int			zeros;
	int			spaces;

	if (!ptr)
		return (print_null_ptr(fmt));
	num = (uintptr_t)ptr;
	digits = nbrlen_u(num, 16);
	zeros = 0;
	if (fmt->flag_zero && !fmt->flag_minus)
		zeros = max_int(0, fmt->width - digits - 2);
	spaces = max_int(0, fmt->width - digits - 2 - zeros);
	count = 0;
	if (!fmt->flag_minus)
		count += put_nchar(' ', spaces);
	count += putstr_n("0x", 2);
	count += put_nchar('0', zeros);
	count += putnbr_base_u(num, "0123456789abcdef");
	if (fmt->flag_minus)
		count += put_nchar(' ', spaces);
	return (count);
}

static int	handle_numeric(va_list args, t_fmt *fmt)
{
	if (fmt->spec == 'd' || fmt->spec == 'i')
		return (print_signed_bonus(va_arg(args, int), fmt));
	if (fmt->spec == 'u')
		return (print_unsigned_dec_bonus(va_arg(args, unsigned int), fmt));
	if (fmt->spec == 'x')
		return (print_unsigned_hex_bonus(va_arg(args, unsigned int), fmt,
				"0123456789abcdefx"));
	if (fmt->spec == 'X')
		return (print_unsigned_hex_bonus(va_arg(args, unsigned int), fmt,
				"0123456789ABCDEFX"));
	return (print_percent_bonus(fmt));
}

int	handle_conversion(va_list args, t_fmt *fmt)
{
	if (fmt->spec == 'c')
		return (print_char_bonus((char)va_arg(args, int), fmt));
	if (fmt->spec == 's')
		return (print_string_bonus(va_arg(args, char *), fmt));
	if (fmt->spec == 'p')
		return (print_pointer_bonus(va_arg(args, void *), fmt));
	if (fmt->spec == '%')
		return (print_percent_bonus(fmt));
	if (fmt->spec == 'd' || fmt->spec == 'i' || fmt->spec == 'u'
		|| fmt->spec == 'x' || fmt->spec == 'X')
		return (handle_numeric(args, fmt));
	return (ft_putchar('%') + ft_putchar(fmt->spec));
}
