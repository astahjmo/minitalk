/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johmatos <johmatos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 17:09:22 by johmatos          #+#    #+#             */
/*   Updated: 2022/11/14 19:27:34 by johmatos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"
#include <signal.h>
#include <stdio.h>


void signal_handler(int sig, siginfo_t *p_info, void *ucontext)
{
	static unsigned char byte = 0;
	static int bit_counter = 0;

	if (sig == SIGUSR2)
		byte |= (1 << bit_counter);
	if (++bit_counter == 8)
	{
		bit_counter = 0;
		ft_printf("%c", byte);
		byte = 0;
	}
	ucontext = ucontext;
	p_info = p_info;
}

int	main(void)
{
	struct sigaction	act;

	act.sa_sigaction = signal_handler;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
	ft_printf("The server pid: %d\n", getpid());
	while (1)
		usleep(300);
}
