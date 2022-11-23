/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johmatos <johmatos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 17:09:22 by johmatos          #+#    #+#             */
/*   Updated: 2022/11/23 01:35:06 by johmatos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"
#include <stdio.h>

void signal_handler(int sig, siginfo_t *p_info, void *ucontext)
{
	static unsigned char utf8_bytes[5];
	static unsigned int byte = 0;

	static int byte_index  = 0;
	static int bit_counter = 0;
	static int num_bytes   = 1;

	if (sig == SIGUSR2) 
		byte |= (1 << bit_counter);
	if (++bit_counter == 8)
	{
		if (byte_index == 0)
		{
			if (byte < 0x80)
				num_bytes = 1;
			else if ((byte & 0xe0) == 0xc0)
				num_bytes = 2;
			else if ((byte & 0xf0) == 0xe0)
				num_bytes = 3;
			else if ((byte & 0xf8) == 0xf0)
				num_bytes = 4;
		}
		if (--num_bytes == 0)
		{
			utf8_bytes[++byte_index] = '\0';
			ft_printf("%s", utf8_bytes);
			byte_index = 0;
		}
		else
			utf8_bytes[byte_index++] = byte;
		bit_counter = 0;
		byte        = 0;

	}

	p_info = p_info;
	ucontext = ucontext;
}
int	main(void)
{
	struct sigaction	act;

	act.sa_sigaction = signal_handler;
	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_NODEFER ;
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
	ft_printf("The server pid: %d\n", getpid());
	while (42)
	pause();
}
