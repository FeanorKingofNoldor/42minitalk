/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuthmay <mhuthmay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 14:06:14 by mhuthmay          #+#    #+#             */
/*   Updated: 2025/01/29 11:12:10 by mhuthmay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

extern volatile sig_atomic_t	g_ack_received;

static int	wait_for_ack(void)
{
	int	timeout;

	timeout = 0;
	while (!g_ack_received && timeout < 50)
	{
		usleep(100);
		timeout++;
	}
	if (!g_ack_received)
		return (0);
	g_ack_received = 0;
	return (1);
}

int	send_bit(pid_t pid, char c, int bit)
{
	if (bit < 0)
		return (1);
	if (c & (1 << bit))
		kill(pid, SIGUSR2);
	else
		kill(pid, SIGUSR1);
	if (!wait_for_ack())
		return (0);
	return (send_bit(pid, c, bit - 1));
}

int	send_char(pid_t pid, char c)
{
	return (send_bit(pid, c, 7));
}

int	send_string(pid_t pid, char *str)
{
	while (*str)
	{
		if (!send_char(pid, *str))
			return (0);
		str++;
	}
	if (!send_char(pid, '\0'))
		return (0);
	return (1);
}
