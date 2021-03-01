/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aglorios <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 15:42:11 by aglorios          #+#    #+#             */
/*   Updated: 2019/10/22 16:43:58 by aglorios         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_three.h"

int		main(int argc, char **argv)
{
	t_one	*one;

	one = global_struct();
	init_struct(one);
	if (argc < 5 || argc > 6)
		return (ft_error(1));
	if (get_value(one, argv, argc) == -1)
		return (ft_error(2));
	if (check_value(one) == 0)
		return (0);
	if (ft_thread_create(one) == 0)
		return (0);
	sem_wait(one->finish);
	if (ft_thread_join(one) == 0)
		return (0);
	return (0);
}