/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mny-aro- <mny-aro-@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 10:00:00 by mny-aro-          #+#    #+#             */
/*   Updated: 2026/03/26 18:22:33 by mny-aro-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_BONUS_H
# define FT_PRINTF_BONUS_H

# include "ft_printf.h"

typedef struct s_fmt
{
	int	flag_minus;
	int	flag_zero;
	int	flag_dot;
	int	flag_hash;
	int	flag_plus;
	int	flag_space;
	int	width;
	int	precision;
	int	spec;
}	t_fmt;

void	fmt_init(t_fmt *fmt);
int		parse_flags(const char *format, int i, t_fmt *fmt);
int		handle_conversion(va_list args, t_fmt *fmt);
int		print_char_bonus(char c, t_fmt *fmt);
int		print_string_bonus(char *s, t_fmt *fmt);
int		print_percent_bonus(t_fmt *fmt);
int		print_signed_bonus(int n, t_fmt *fmt);
int		print_unsigned_dec_bonus(unsigned int n, t_fmt *fmt);
int		print_unsigned_hex_bonus(unsigned long num, t_fmt *fmt,
			const char *base);
int		print_pointer_bonus(void *ptr, t_fmt *fmt);

size_t	ft_strlen_bonus(const char *s);
int		put_nchar(char c, int n);
int		max_int(int a, int b);
int		nbrlen_u(unsigned long n, int base);
int		putnbr_base_u(unsigned long n, const char *digits);
int		putstr_n(const char *s, int n);

#endif
