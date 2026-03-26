/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_bonus_part2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mny-aro- <mny-aro-@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 18:20:00 by mny-aro-          #+#    #+#             */
/*   Updated: 2026/03/26 18:30:58 by mny-aro-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

static void	calc_signed(t_fmt *fmt, int n, unsigned int *num,
				unsigned int pad[4])
{
	pad[3] = 0;
	if (n < 0)
	{
		*num = (unsigned long)(-(long)n);
		pad[3] = '-';
	}
	else
	{
		*num = (unsigned long)n;
		if (fmt->flag_plus)
			pad[3] = '+';
		else if (fmt->flag_space)
			pad[3] = ' ';
	}
	pad[0] = nbrlen_u(*num, 10);
	if (fmt->flag_dot && fmt->precision == 0 && n == 0)
		pad[0] = 0;
	pad[1] = 0;
	if (fmt->flag_dot)
		pad[1] = max_int(0, fmt->precision - pad[0]);
	else if (fmt->flag_zero && !fmt->flag_minus)
		pad[1] = max_int(0, fmt->width - pad[0] - (pad[3] != 0));
	pad[2] = max_int(0, fmt->width - pad[0] - pad[1] - (pad[3] != 0));
}

int	print_signed_bonus(int n, t_fmt *fmt)
{
	unsigned int	num;
	unsigned int	pad[4];
	unsigned int	count;

	calc_signed(fmt, n, &num, pad);
	count = 0;
	if (!fmt->flag_minus)
		count += put_nchar(' ', pad[2]);
	if (pad[3])
		count += ft_putchar((char)pad[3]);
	count += put_nchar('0', pad[1]);
	if (pad[0])
		count += putnbr_base_u(num, "0123456789");
	if (fmt->flag_minus)
		count += put_nchar(' ', pad[2]);
	return (count);
}

int	print_unsigned_dec_bonus(unsigned int n, t_fmt *fmt)
{
	int	count;
	int	digits;
	int	zeros;
	int	spaces;

	digits = nbrlen_u(n, 10);
	if (fmt->flag_dot && fmt->precision == 0 && n == 0)
		digits = 0;
	zeros = 0;
	if (fmt->flag_dot)
		zeros = max_int(0, fmt->precision - digits);
	else if (fmt->flag_zero && !fmt->flag_minus)
		zeros = max_int(0, fmt->width - digits);
	spaces = max_int(0, fmt->width - digits - zeros);
	count = 0;
	if (!fmt->flag_minus)
		count += put_nchar(' ', spaces);
	count += put_nchar('0', zeros);
	if (digits)
		count += putnbr_base_u(n, "0123456789");
	if (fmt->flag_minus)
		count += put_nchar(' ', spaces);
	return (count);
}

static void	calc_hex(unsigned long num, t_fmt *fmt, int pad[4])
{
	pad[0] = nbrlen_u(num, 16);
	if (fmt->flag_dot && fmt->precision == 0 && num == 0)
		pad[0] = 0;
	pad[1] = 0;
	if (fmt->flag_hash && num != 0)
		pad[1] = 2;
	pad[2] = 0;
	if (fmt->flag_dot)
		pad[2] = max_int(0, fmt->precision - pad[0]);
	else if (fmt->flag_zero && !fmt->flag_minus)
		pad[2] = max_int(0, fmt->width - pad[0] - pad[1]);
	pad[3] = max_int(0, fmt->width - pad[0] - pad[2] - pad[1]);
}

int	print_unsigned_hex_bonus(unsigned long num, t_fmt *fmt, const char *base)
{
	int	count;
	int	pad[4];

	calc_hex(num, fmt, pad);
	count = 0;
	if (!fmt->flag_minus)
		count += put_nchar(' ', pad[3]);
	if (pad[1])
	{
		count += ft_putchar('0');
		count += ft_putchar(base[16]);
	}
	count += put_nchar('0', pad[2]);
	if (pad[0])
	{
		if (base[16] == 'x')
			count += putnbr_base_u(num, "0123456789abcdef");
		else
			count += putnbr_base_u(num, "0123456789ABCDEF");
	}
	if (fmt->flag_minus)
		count += put_nchar(' ', pad[3]);
	return (count);
}
