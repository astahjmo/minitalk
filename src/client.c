/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johmatos <johmatos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 17:09:05 by johmatos          #+#    #+#             */
/*   Updated: 2022/11/07 15:36:31 by johmatos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

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
	pid = pid;
	return (0);
}

int	main(int argc, char *argv[])
{
	int		a;
	char	*b;

	if (argc != 3)
		return (ft_printf("Wrong usage"));
	a = ft_atoi(argv[1]);
	ft_printf("Send a signal to a server pid: %d\n", a);
	b = &argv[2][0];
	while (*b != '\0')
		send_sig(a, *(b)++);
}
