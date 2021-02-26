/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aglorios <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 15:42:11 by aglorios          #+#    #+#             */
/*   Updated: 2021/02/25 14:06:55 by aglorios         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_two.h"

int		ft_error(int i)
{
	if (i == 1)
		write(2, "Nbr of arguments ", 17);
	if (i == 2)
		write(2, "Invalid character ", 18);
	if (i == 3)
		write(2, "Not enough Philo ", 17);
	write(2, ": ERROR\n", 8);
	return (0);
}

void	init_struct(t_one *one)
{
	one->nb_of_philo = 0;
	one->t_to_die = 0;
	one->t_to_eat = 0;
	one->t_to_sleep = 0;
	one->nb_of_time = 0;
	one->death = 0;
}

t_one	*global_struct(void)
{
	static t_one	one;

	return (&one);
}
