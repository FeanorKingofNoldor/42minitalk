/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuthmay <mhuthmay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 16:57:58 by mhuthmay          #+#    #+#             */
/*   Updated: 2024/09/19 17:08:38 by mhuthmay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_print_hex_common(unsigned int num, const char *hex_digits)
{
	char	buffer[9];
	int		i;
	int		count;	

	i = 8;
	count = 0;
	buffer[i] = '\0';
	if (num == 0)
	{
		ft_putchar_fd('0', 1);
		return (1);
	}
	while (num > 0)
	{
		i--;
		buffer[i] = hex_digits[num % 16];
		num /= 16;
	}
	ft_putstr_fd(&buffer[i], 1);
	count = 8 - i;
	return (count);
}

static int	ft_print_hex_lower_internal(unsigned int num)
{
	const char	*hex_digits;

	hex_digits = "0123456789abcdef";
	return (ft_print_hex_common(num, hex_digits));
}

static int	ft_print_hex_upper_internal(unsigned int num)
{
	const char	*hex_digits;

	hex_digits = "0123456789ABCDEF";
	return (ft_print_hex_common(num, hex_digits));
}

int	ft_print_hex_lower(va_list argptr)
{
	unsigned int	num;

	num = va_arg(argptr, unsigned int);
	return (ft_print_hex_lower_internal(num));
}

int	ft_print_hex_upper(va_list argptr)
{
	unsigned int	num;

	num = va_arg(argptr, unsigned int);
	return (ft_print_hex_upper_internal(num));
}
