/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuthmay <mhuthmay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 15:00:09 by mhuthmay          #+#    #+#             */
/*   Updated: 2024/09/19 17:11:25 by mhuthmay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include "libft.h"

int	ft_print_char(va_list argptr);
int	ft_print_string(va_list argptr);
int	ft_print_pointer(va_list argptr);
int	ft_print_integer(va_list argptr);
int	ft_print_unsigned(va_list argptr);
int	ft_print_hex_lower(va_list argptr);
int	ft_print_hex_upper(va_list argptr);
int	ft_print_percent(void);
int	ft_printf(const char *format, ...);

#endif
