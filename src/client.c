/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johmatos <johmatos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 17:09:05 by johmatos          #+#    #+#             */
/*   Updated: 2022/11/26 14:26:34 by johmatos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

static void	signal_handler(int sig)
{
	g_sema = TRUE;
	ft_printf("received 1 bit with success\n", sig);
}

static int	send_sig(int pid, unsigned char b)
{
	int	a;

	a = 0;
	while (a < 8)
	{
		g_sema = FALSE;
		if (b & 1)
		{
			if (kill(pid, SIGUSR2) == ERROR)
				return (FALSE);
		}
		else
		{
			if (kill(pid, SIGUSR1) == ERROR)
				return (FALSE);
		}
		b = b >> 1;
		a++;
		while (!g_sema)
			;
	}
	return (TRUE);
}

static int	check_args(char *pid)
{
	while (*pid != '\0')
	{
		if (!ft_isdigit(*pid))
			return (FALSE);
		pid++;
	}
	return (TRUE);
}

int	main(int argc, char *argv[])
{
	int					a;
	char				*b;
	struct sigaction	act;

	if (argc != 3)
		return (ft_printf("Wrong usage"));
	if (!check_args(argv[1]))
		return (ft_printf("Wrong pid"));
	act.sa_handler = signal_handler;
	act.sa_flags = 0;
	sigemptyset(&act.sa_mask);
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
	a = ft_atoi(argv[1]);
	b = &argv[2][0];
	while (*b != '\0')
		if (!send_sig(a, *(b)++))
			return (ft_printf("Error on sending signal"));
}
