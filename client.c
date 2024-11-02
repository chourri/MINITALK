/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chourri <chourri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:40:12 by chourri           #+#    #+#             */
/*   Updated: 2024/06/01 20:24:29 by chourri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	encrypt_and_send_char(pid_t server_PID, char c)
{
	int	i_th_bit;

	i_th_bit = 0;
	while (i_th_bit < 8)
	{
		if (c & (1 << i_th_bit))
		{
			if (kill(server_PID, SIGUSR1) == -1)
				error();
		}
		else
		{
			if (kill(server_PID, SIGUSR2) == -1)
				error();
		}
		usleep(800);
		i_th_bit++;
	}
}

int	ft_atoi(const char *str)
{
	int	sign;
	int	res;
	int	i;

	res = 0;
	sign = 1;
	i = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
		sign *= -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] <= '9' && str[i] >= '0')
	{
		res = ((str[i] - 48) + (res * 10));
		i++;
	}
	return (res * sign);
}

void	send_string(pid_t server_PID, char *str)
{
	int	i;

	i = 0;
	while (str[i])
		encrypt_and_send_char(server_PID, str[i++]);
	encrypt_and_send_char(server_PID, '\0');
}

int	main(int ac, char **av)
{
	pid_t	server_pid;

	if (ac != 3)
		error();
	handle_pid(av[1]);
	server_pid = ft_atoi (av[1]);
	if (server_pid < 1)
		error ();
	send_string(server_pid, av[2]);
	return (0);
}
