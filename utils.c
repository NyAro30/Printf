/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mny-aro- <mny-aro-@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 09:06:49 by mny-aro-          #+#    #+#             */
/*   Updated: 2026/03/04 10:58:01 by mny-aro-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int parse_width(const char *format, int *i)
{
    int result;
    int digit;
    
    result = 0;

    while (format[*i] >= '0' && format[*i] <= '9')
    {
        digit = format[*i] - '0';
        result = result * 10 + digit;
        (*i)++;
    }
    return (result);
}

int count_digits(int n)
{
    int len;

    len = 0;    
    if (n == 0)
        return (1);
	if (n == -2147483648)
		return (11);
    if (n < 0)
    {
        n = -n;
        len = 1;
    }
    while (n > 0)
    {
        len++;
        n = n / 10;
    }
    return (len);
}

int ft_putnbr_width(int n, int width)
{
    int len;
    int padding;
    int	count;
	
    len = count_digits(n);
    padding = width - len;
	count = 0;
    
    while (padding > 0)
    {
        count += ft_putchar(' ');
        padding--;
    }
    count += ft_putnbr(n);
    return (count);
}

int	ft_putchar_width(char c, int width)
{
	int	padding;
	int	count;
	
	padding = width - 1;
	count = 0;
	while (padding > 0)
	{
		count += ft_putchar(' ');
		padding--;
	}
	count += ft_putchar(c);
	return (count);
}

int ft_putstr_width(char *s, int width)
{
    int padding;
    int count;
    int len;

    if (s == NULL)
        return (ft_putstr_width("(null)", width)); 
    len = ft_strlen(s);
    padding = width - len;
    count = 0;
    while (padding > 0)
    {
        count += ft_putchar(' ');
        padding--;
    }
    count += ft_putstr(s);
    return (count);
}
