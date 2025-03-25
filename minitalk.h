/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuthmay <mhuthmay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 10:51:39 by mhuthmay          #+#    #+#             */
/*   Updated: 2025/01/29 11:14:55 by mhuthmay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# define _POSIX_C_SOURCE 199309L
# define _DEFAULT_SOURCE
# define _XOPEN_SOURCE 500

# include "libft/ft_printf.h"
# include "libft/libft.h"
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/signal.h>
# include <sys/types.h>
# include <unistd.h>

# define MAX_MESSAGE_SIZE 131072

typedef struct s_message
{
	char	*buffer;
	size_t	current_byte;
	size_t	current_bit;
	pid_t	client_pid;
	int		transmission_complete;
}		t_message;

// Server function prototypes
void	handle_signal(int signum, siginfo_t *info, void *context);
void	reset_message_state(void);
void	cleanup_and_exit(int status);
int		init_message_buffer(pid_t client_pid);
int		process_complete_byte(unsigned char byte, pid_t client_pid);

// Client function prototypes
void	handle_ack(int signum);
int		setup_signals(void);
pid_t	parse_pid(char *str);
int		send_bit(pid_t pid, char c, int bit);
int		send_char(pid_t pid, char c);
int		send_string(pid_t pid, char *str);

#endif