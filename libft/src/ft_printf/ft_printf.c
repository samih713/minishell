/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 16:32:12 by tanas             #+#    #+#             */
/*   Updated: 2023/07/08 14:53:34 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_format(const char format, va_list args)
{
	int	len;

	len = 0;
	if (format == 'c')
		len += ft_print_char(va_arg(args, int));
	else if (format == 's')
		len += ft_print_string(va_arg(args, char *));
	else if (format == 'p')
	{
		len += write(1, "0x", 2);
		len += ft_print_pointer(va_arg(args, size_t), "0123456789abcdef");
	}
	else if (format == 'i' || format == 'd')
		len += ft_print_number(va_arg(args, int));
	else if (format == 'u')
		len += ft_print_unsigned(va_arg(args, unsigned int));
	else if (format == 'x')
		len += ft_print_hex(va_arg(args, unsigned int), "0123456789abcdef");
	else if (format == 'X')
		len += ft_print_hex(va_arg(args, unsigned int), "0123456789ABCDEF");
	else if (format == '%')
		len += write(1, "%", 1);
	return (len);
}

int	ft_printf(const char *str, ...)
{
	int		i;
	int		length_of_print;
	va_list	args;

	i = 0;
	length_of_print = 0;
	if (!str)
		return (0);
	va_start(args, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			length_of_print += ft_format(str[i + 1], args);
			i++;
		}
		else
			length_of_print += ft_print_char(str[i]);
		i++;
	}
	va_end(args);
	return (length_of_print);
}
