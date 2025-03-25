/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_integer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuthmay <mhuthmay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 16:56:07 by mhuthmay          #+#    #+#             */
/*   Updated: 2024/09/19 17:08:43 by mhuthmay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_integer(va_list argptr)
{
	int		num;
	int		count;
	char	*str;

	num = va_arg(argptr, int);
	count = 0;
	str = ft_itoa(num);
	if (!str)
		return (0);
	ft_putstr_fd(str, 1);
	count = ft_strlen(str);
	free(str);
	return (count);
}
