/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mny-aro- <mny-aro-@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 10:00:00 by mny-aro-          #+#    #+#             */
/*   Updated: 2026/03/26 18:15:16 by mny-aro-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

size_t	ft_strlen_bonus(const char *s)
{
	size_t	len;

	len = 0;
	while (s && s[len])
		len++;
	return (len);
}

int	put_nchar(char c, int n)
{
	int	count;

	count = 0;
	while (n-- > 0)
		count += ft_putchar(c);
	return (count);
}

int	max_int(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

int	nbrlen_u(unsigned long n, int base)
{
	int	len;

	len = 1;
	while (n >= (unsigned long)base)
	{
		n /= (unsigned long)base;
		len++;
	}
	return (len);
}
