/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aglorios <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 15:42:11 by aglorios          #+#    #+#             */
/*   Updated: 2019/10/22 16:43:58 by aglorios         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_one.h"

int		main(int argc, char **argv)
{
	t_one	*one;
	t_data	*data;

	one = global_struct();
	data = global_structdata();
	init_struct(one, data);
	if (argc < 5 || argc > 6)
		return (ft_error(1));
	if (get_value(one, argv, argc) == -1)
		return (ft_error(2));
	if (check_value(one) == 0)
		return (0);
	if (ft_thread_create(one) == 0)
		return (0);
	if (ft_thread_join(one) == 0)
		return (0);
	printf("OK\n");
	return (0);
}
