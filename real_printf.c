if (format[i] == '%')
{
	int width;
	
    i++;
	width = 0;
    if (format[i] >= '0' && format[i] <= '9')
        width = parse_width(format, &i);
    if (format[i] == 'd' || format[i] == 'i')
    {
        if (width > 0)
            count += ft_putnbr_width(va_arg(args, int), width);
        else
            count += ft_putnbr(va_arg(args, int));
    }
    else
        count += ft_check_format(format[i], args);
    i++;
}