/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mny-aro- <mny-aro-@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 10:00:00 by mny-aro-          #+#    #+#             */
/*   Updated: 2026/03/26 18:18:59 by mny-aro-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

void	fmt_init(t_fmt *fmt)
{
	fmt->flag_minus = 0;
	fmt->flag_zero = 0;
	fmt->flag_dot = 0;
	fmt->flag_hash = 0;
	fmt->flag_plus = 0;
	fmt->flag_space = 0;
	fmt->width = 0;
	fmt->precision = 0;
	fmt->spec = 0;
}

static void	read_number(const char *format, int *i, int *out)
{
	*out = 0;
	while (format[*i] >= '0' && format[*i] <= '9')
	{
		*out = (*out * 10) + (format[*i] - '0');
		(*i)++;
	}
}

static void	set_flag(t_fmt *fmt, char c)
{
	if (c == '-')
		fmt->flag_minus = 1;
	else if (c == '0')
		fmt->flag_zero = 1;
	else if (c == '#')
		fmt->flag_hash = 1;
	else if (c == '+')
		fmt->flag_plus = 1;
	else if (c == ' ')
		fmt->flag_space = 1;
}

static void	normalize_flags(t_fmt *fmt)
{
	if (fmt->flag_minus)
		fmt->flag_zero = 0;
	if (fmt->flag_plus)
		fmt->flag_space = 0;
}

int	parse_flags(const char *format, int i, t_fmt *fmt)
{
	while (format[i] == '-' || format[i] == '0' || format[i] == '#'
		|| format[i] == '+' || format[i] == ' ')
	{
		set_flag(fmt, format[i]);
		i++;
	}
	if (format[i] >= '0' && format[i] <= '9')
		read_number(format, &i, &fmt->width);
	if (format[i] == '.')
	{
		fmt->flag_dot = 1;
		i++;
		read_number(format, &i, &fmt->precision);
	}
	normalize_flags(fmt);
	fmt->spec = format[i];
	return (i);
}
