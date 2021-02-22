/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_things.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aglorios <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 15:42:11 by aglorios          #+#    #+#             */
/*   Updated: 2019/10/22 16:43:58 by aglorios         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_one.h"

void	*eating(void *arg)
{
	t_one	*one;

	one = global_struct();
	printf("philos ||%s|| ||EATING||\n\n", (char *)arg);
	sleep(one->t_to_eat);
	return (NULL);
}

void	*sleeping(void *arg)
{
	t_one	*one;

	one = global_struct();
	(void)arg;
	printf("philos ||%s|| SLEEPING\n\n", (char *)arg);
	sleep(one->t_to_sleep);
	return (NULL);
}

void	choose_fork(t_one *one, t_data *data, int i)
{
	data->fork1 = 0;
	data->fork2 = 0;
	if (i + 1 >= one->nb_of_philo)
		data->fork1 = 0;
	else
		data->fork1 = i + 1;
	data->fork2 = i;
	if (i % 2)
	{
		data->fork2 = data->fork1;
		data->fork1 = i;
	}
}

void	things_bcl(t_one *one, t_data *data, void *arg)
{
	pthread_mutex_lock(one->mutex[data->fork1]);
	printf("philos ||%s|| a la fourchette |%i|\n\n", (char *)arg, data->fork1);
	pthread_mutex_lock(one->mutex[data->fork2]);
	printf("philos ||%s|| a la fourchette |%i|\n\n", (char *)arg, data->fork2);
	eating(arg);
	pthread_mutex_unlock(one->mutex[data->fork1]);
	pthread_mutex_unlock(one->mutex[data->fork2]);
	sleeping(arg);
	printf("philos ||%s|| THINKING\n\n", (char *)arg);
}

void	*do_things(void *arg)
{
	t_one	*one;
	t_data	*data;
	int		i;

	one = global_struct();
	data = global_structdata();
	if (!(data = malloc(sizeof(t_data))))
		return (NULL);
	i = ft_atoi((char *)arg) - 1;
	choose_fork(one, data, i);
	printf("philos ||%s|| THINKING\n\n", (char *)arg);
	while (1)
		things_bcl(one, data, arg);
	return (NULL);
}
