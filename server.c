/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chourri <chourri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 10:08:32 by chourri           #+#    #+#             */
/*   Updated: 2024/06/01 20:52:56 by chourri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	handle_signal(int Signal, siginfo_t *info, void *u)
{
	static char		c;
	static int		i_th_bit;
	static pid_t	pid;

	(void)u;
	if (!pid || pid != info->si_pid)
	{
		c = 0;
		i_th_bit = 0;
		pid = info->si_pid;
	}
	if (Signal == SIGUSR1)
		c |= (1 << i_th_bit);
	i_th_bit++;
	if (i_th_bit == 8)
	{
		if (c == '\0')
			write (1, "\n", 1);
		else
			write (1, &c, 1);
		c = 0;
		i_th_bit = 0;
	}
}

void	ft_putnbr(int n)
{
	char	c;

	if (n > 10)
		ft_putnbr(n / 10);
	c = n % 10 + '0';
	write (1, &c, 1);
}

int	main(int ac, char **av)
{
	struct sigaction	s_action;
	pid_t				pid;

	(void)ac;
	(void)av;
	s_action.sa_sigaction = &handle_signal;
	s_action.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &s_action, NULL);
	sigaction(SIGUSR2, &s_action, NULL);
	write (1, "PID is : ", 9);
	pid = getpid();
	ft_putnbr(pid);
	write (1, "\n", 1);
	while (true)
		pause();
	return (0);
}
