/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aglorios <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 15:42:11 by aglorios          #+#    #+#             */
/*   Updated: 2021/03/10 15:25:12 by aglorios         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_three.h"

int		main(int argc, char **argv)
{
	t_one	*one;
	int		i;

	one = global_struct();
	init_struct(one);
	i = 0;
	if (argc < 5 || argc > 6)
		return (ft_error(1));
	i = get_value(one, argv, argc);
	if (i == -1)
		return (ft_error(2));
	if (i == -2)
		return (ft_error(4));
	if (check_value(one) == 0)
		return (0);
	if (ft_thread_create(one) == 0)
		return (0);
	i = 0;
	while (i++ < one->nb_of_philo)
		sem_wait(one->sem_eat);
	sem_wait(one->finish);
	if (ft_thread_join(one) == 0)
		return (0);
	return (0);
}
