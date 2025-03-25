/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuthmay <mhuthmay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 14:46:22 by mhuthmay          #+#    #+#             */
/*   Updated: 2024/09/19 17:09:09 by mhuthmay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	handle_format_specifier(const char **format, va_list argptr)
{
	int	count;

	count = 0;
	if (**format == 'c')
		count += ft_print_char(argptr);
	else if (**format == 's')
		count += ft_print_string(argptr);
	else if (**format == 'p')
		count += ft_print_pointer(argptr);
	else if (**format == 'd' || **format == 'i')
		count += ft_print_integer(argptr);
	else if (**format == 'u')
		count += ft_print_unsigned(argptr);
	else if (**format == 'x')
		count += ft_print_hex_lower(argptr);
	else if (**format == 'X')
		count += ft_print_hex_upper(argptr);
	else if (**format == '%')
		count += ft_print_percent();
	return (count);
}

static int	process_format_string(const char *format, va_list argptr)
{
	int	count;

	count = 0;
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			count += handle_format_specifier(&format, argptr);
		}
		else
		{
			ft_putchar_fd(*format, 1);
			count++;
		}
		format++;
	}
	return (count);
}

int	ft_printf(const char *format, ...)
{
	va_list	argptr;
	int		count;

	count = 0;
	va_start(argptr, format);
	if (format == NULL)
		return (-1);
	count = process_format_string(format, argptr);
	va_end(argptr);
	return (count);
}
