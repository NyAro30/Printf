/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mny-aro- <mny-aro-@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 10:46:29 by mny-aro-          #+#    #+#             */
/*   Updated: 2026/02/18 10:47:04 by mny-aro-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr_hex(unsigned long n, char alpha)
{
	char	c;
	int		count;

	count = 0;
	if (n >= 16)
		count += ft_putnbr_hex((n / 16), alpha);
	if ((n % 16) < 10)
		c = (n % 16) + '0';
	else
	{
		if (alpha == 'x')
			c = (n % 16) - 10 + 'a';
		else
			c = (n % 16) - 10 + 'A';
	}
	count += ft_putchar(c);
	return (count);
}
