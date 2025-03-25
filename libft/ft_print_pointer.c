/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_pointer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuthmay <mhuthmay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 16:54:53 by mhuthmay          #+#    #+#             */
/*   Updated: 2024/09/19 17:08:53 by mhuthmay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_print_hex_ptr(unsigned long num)
{
	char	*hex_digits;
	char	buffer[17];
	int		i;
	int		count;

	hex_digits = "0123456789abcdef";
	i = 16;
	count = 0;
	buffer[16] = '\0';
	if (num == 0)
	{
		i--;
		buffer[i] = '0';
	}
	while (num > 0)
	{
		i--;
		buffer[i] = hex_digits[num % 16];
		num /= 16;
	}
	ft_putstr_fd(&buffer[i], 1);
	count = 16 - i;
	return (count);
}

int	ft_print_pointer(va_list argptr)
{
	void			*ptr;
	unsigned long	num;
	int				count;

	ptr = va_arg(argptr, void *);
	if (ptr == NULL)
	{
		ft_putstr_fd("(nil)", 1);
		return (5);
	}
	num = (unsigned long)ptr;
	count = 0;
	ft_putstr_fd("0x", 1);
	count += 2;
	count += ft_print_hex_ptr(num);
	return (count);
}
