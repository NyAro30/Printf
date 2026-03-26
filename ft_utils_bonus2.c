/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_bonus2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mny-aro- <mny-aro-@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 18:20:00 by mny-aro-          #+#    #+#             */
/*   Updated: 2026/03/26 18:27:38 by mny-aro-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

int	putnbr_base_u(unsigned long n, const char *digits)
{
	int	count;
	int	base;

	count = 0;
	base = ft_strlen_bonus(digits);
	if (n >= (unsigned long)base)
		count += putnbr_base_u(n / (unsigned long)base, digits);
	count += ft_putchar(digits[n % (unsigned long)base]);
	return (count);
}

int	putstr_n(const char *s, int n)
{
	int	count;

	count = 0;
	while (s && *s && n-- > 0)
		count += ft_putchar(*s++);
	return (count);
}
