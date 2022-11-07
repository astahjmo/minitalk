/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johmatos <johmatos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 17:09:22 by johmatos          #+#    #+#             */
/*   Updated: 2022/11/07 16:16:10 by johmatos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"
#include <signal.h>

unsigned char	reverse(unsigned char b)
{
	b = (b & 0xF0) >> 4 | (b & 0x0F) << 4;
	b = (b & 0xCC) >> 2 | (b & 0x33) << 2;
	b = (b & 0xAA) >> 1 | (b & 0x55) << 1;
	return (b);
}

void	signal_handler(int sig)
{
	static unsigned int		a = 0;
	static unsigned int		b = 0;

	a <<= 1;
	if (sig == SIGUSR2)
		a++;
	b++;
	if (b == 8)
	{
		b = 0;
		ft_printf("%c", reverse(a));
	}
}

int	main(void)
{
	struct sigaction	act;

	act.sa_handler = &signal_handler;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
	ft_printf("The server pid: %d\n", getpid());
	while (1)
		usleep(300);
}
