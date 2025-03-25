/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuthmay <mhuthmay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 10:51:48 by mhuthmay          #+#    #+#             */
/*   Updated: 2025/01/29 11:15:28 by mhuthmay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

t_message	g_message_state;

static void	handle_termination(int signum)
{
	(void)signum;
	cleanup_and_exit(0);
}

static void	handle_timeout(int signum)
{
	(void)signum;
	if (g_message_state.buffer && g_message_state.current_byte > 0)
	{
		if (g_message_state.client_pid && kill(g_message_state.client_pid,
				SIGUSR2) < 0)
			write(2, "Error: Failed to send timeout signal\n", 35);
		reset_message_state();
	}
}

static int	setup_server_signals(void)
{
	struct sigaction	sa;
	struct sigaction	sa_term;
	struct sigaction	sa_timeout;

	sa.sa_sigaction = handle_signal;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sa_term.sa_handler = handle_termination;
	sa_term.sa_flags = 0;
	sigemptyset(&sa_term.sa_mask);
	sa_timeout.sa_handler = handle_timeout;
	sa_timeout.sa_flags = 0;
	sigemptyset(&sa_timeout.sa_mask);
	if (sigaction(SIGUSR1, &sa, NULL) == -1 || sigaction(SIGUSR2, &sa, NULL)
		== -1 || sigaction(SIGINT, &sa_term, NULL) == -1 || sigaction(SIGTERM,
			&sa_term, NULL) == -1 || sigaction(SIGALRM, &sa_timeout, NULL)
		== -1)
		return (0);
	return (1);
}

void	handle_signal(int signum, siginfo_t *info, void *context)
{
	static unsigned char	current_char = 0;

	(void)context;
	if (!init_message_buffer(info->si_pid))
		return ;
	if (g_message_state.client_pid != info->si_pid)
		return ;
	if (signum == SIGUSR2)
		current_char |= (1 << (7 - g_message_state.current_bit));
	g_message_state.current_bit++;
	if (kill(info->si_pid, SIGUSR1) < 0)
	{
		reset_message_state();
		return ;
	}
	if (g_message_state.current_bit == 8)
	{
		if (!process_complete_byte(current_char, info->si_pid))
			return ;
		current_char = 0;
		g_message_state.current_bit = 0;
	}
}

int	main(void)
{
	ft_memset(&g_message_state, 0, sizeof(t_message));
	ft_printf("Server PID: %d\n", getpid());
	if (!setup_server_signals())
	{
		write(2, "Error: Failed to set up signal handlers\n", 38);
		return (1);
	}
	while (1)
		pause();
	return (0);
}
