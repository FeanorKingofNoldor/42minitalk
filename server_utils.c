/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuthmay <mhuthmay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 09:59:13 by mhuthmay          #+#    #+#             */
/*   Updated: 2025/01/29 11:12:30 by mhuthmay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

extern t_message	g_message_state;

void	reset_message_state(void)
{
	if (g_message_state.buffer)
	{
		ft_bzero(g_message_state.buffer, MAX_MESSAGE_SIZE);
		free(g_message_state.buffer);
		g_message_state.buffer = NULL;
	}
	g_message_state.current_byte = 0;
	g_message_state.current_bit = 0;
	g_message_state.client_pid = 0;
	g_message_state.transmission_complete = 0;
}

void	cleanup_and_exit(int status)
{
	if (g_message_state.client_pid)
		kill(g_message_state.client_pid, SIGUSR2);
	reset_message_state();
	exit(status);
}

int	init_message_buffer(pid_t client_pid)
{
	if (kill(client_pid, 0) < 0)
	{
		reset_message_state();
		return (0);
	}
	if (!g_message_state.buffer)
	{
		g_message_state.buffer = (char *)malloc(MAX_MESSAGE_SIZE);
		if (!g_message_state.buffer)
			return (0);
		ft_bzero(g_message_state.buffer, MAX_MESSAGE_SIZE);
		g_message_state.client_pid = client_pid;
	}
	else if (g_message_state.client_pid != client_pid)
		return (0);
	return (1);
}

int	process_complete_byte(unsigned char byte, pid_t client_pid)
{
	if (g_message_state.current_byte >= MAX_MESSAGE_SIZE - 1)
	{
		if (kill(client_pid, SIGUSR2) < 0)
			write(2, "Error: Failed to send error signal\n", 33);
		reset_message_state();
		return (0);
	}
	g_message_state.buffer[g_message_state.current_byte++] = byte;
	if (byte == '\0')
	{
		if (g_message_state.current_byte > 1)
			if (write(1, g_message_state.buffer, g_message_state.current_byte
					- 1) < 0 || write(1, "\n", 1) < 0)
				return (0);
		if (kill(client_pid, SIGUSR1) < 0)
			write(2, "Error: Failed to send ACK\n", 25);
		reset_message_state();
	}
	return (1);
}
