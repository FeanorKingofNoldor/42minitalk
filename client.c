/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuthmay <mhuthmay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 10:51:43 by mhuthmay          #+#    #+#             */
/*   Updated: 2025/01/29 11:15:54 by mhuthmay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

volatile sig_atomic_t	g_ack_received = 0;

void	handle_ack(int signum)
{
	(void)signum;
	g_ack_received = 1;
}

int	check_server_pid(pid_t pid)
{
	if (pid <= 0 || pid == -1)
	{
		write(2, "Error: Invalid PID number\n", 25);
		return (0);
	}
	if (kill(pid, 0) < 0)
	{
		write(2, "Error: Server not found\n", 23);
		return (0);
	}
	return (1);
}

int	setup_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = handle_ack;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
	{
		write(2, "Error: Failed to set up signal handler\n", 37);
		return (0);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	pid_t	server_pid;

	if (argc != 3)
	{
		write(2, "Usage: ./client [server_pid] [string]\n", 37);
		return (1);
	}
	server_pid = ft_atoi(argv[1]);
	if (!check_server_pid(server_pid) || !setup_signals())
		return (1);
	if (ft_strlen(argv[2]) > MAX_MESSAGE_SIZE)
	{
		write(2, "Error: Message too long\n", 23);
		return (1);
	}
	if (!send_string(server_pid, argv[2]))
		write(2, "Error: Transmission failed\n", 26);
	return (0);
}
