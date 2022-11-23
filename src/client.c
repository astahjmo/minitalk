/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johmatos <johmatos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 17:09:05 by johmatos          #+#    #+#             */
/*   Updated: 2022/11/22 16:36:50 by johmatos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

void signal_handler(int sig)
{
	ft_printf("received signal: %d\n", sig);
}
int	send_sig(int pid, unsigned char b)
{
	int	a;

	a = 0;
	while (a < 8)
	{
		if (b & 1)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		b = b >> 1;
		a++;
		usleep(1000);
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	int		a;
	char	*b;
	struct sigaction	act;

	if (argc != 3)
		return (ft_printf("Wrong usage"));

	act.sa_handler = signal_handler;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
	a = ft_atoi(argv[1]);
	b = &argv[2][0];
	while (*b != '\0')
	{
		send_sig(a, *(b)++);
	}
}
