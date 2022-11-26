/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johmatos <johmatos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 17:09:22 by johmatos          #+#    #+#             */
/*   Updated: 2022/11/25 21:33:44 by johmatos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

void	signal_handler(int sig, siginfo_t *p_info, void *ucontext)
{
	static int	byte = 0;
	static int	bit_counter = 0;

	if (sig == SIGUSR2)
		byte |= (1 << bit_counter);
	if (++bit_counter == 8)
	{
		ft_putchar_fd(byte, 1);
		bit_counter = 0;
		byte = 0;
	}
	kill(p_info->si_pid, SIGUSR1);
	(void)ucontext;
}

int	main(void)
{
	struct sigaction	act;

	act.sa_sigaction = signal_handler;
	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
	ft_printf("The server pid: %d\n", getpid());
	while (42)
		pause();
}
