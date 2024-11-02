/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chourri <chourri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 15:13:29 by chourri           #+#    #+#             */
/*   Updated: 2024/06/01 18:24:22 by chourri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	error(void)
{
	write (1, "Error\n", 6);
	exit(EXIT_FAILURE);
}

int	is_space(char *s)
{
	while (*s)
	{
		if (!(*s == ' ' || (*s >= 9 && *s <= 13)))
			return (0);
		s++;
	}
	return (1);
}

void	handle_pid(char *av)
{
	int	i;

	i = 0;
	if (is_space(av))
		error();
	if (!av || av[0] == '\0')
		error();
	while (av[i] == ' ' || (av[i] >= 9 && av[i] <= 13))
		i++;
	if (av[i] == '-')
		error();
	else if (av[i] == '+')
		i++;
	while (av[i])
	{
		if (!(av[i] >= '0' && av[i] <= '9'))
			error();
		i++;
	}
}
