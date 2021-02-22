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

void	*eating(void *arg, t_data *data)
{
	t_one	*one;

	one = global_struct();
	ft_put_status(one, data, (char *)arg, "EATING", -1);
	usleep(one->t_to_eat * 1000);
	return (NULL);
}

void	*sleeping(void *arg, t_data *data)
{
	t_one	*one;

	one = global_struct();
	ft_put_status(one, data, (char *)arg, "SLEEPING", -1);
	usleep(one->t_to_sleep * 1000);
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
	ft_put_status(one, data, (char *)arg, NULL, data->fork1);
	pthread_mutex_lock(one->mutex[data->fork2]);
	ft_put_status(one, data, (char *)arg, NULL, data->fork2);
	eating(arg, data);
	pthread_mutex_unlock(one->mutex[data->fork1]);
	pthread_mutex_unlock(one->mutex[data->fork2]);
	sleeping(arg, data);
}

void	*do_things(void *arg)
{
	t_one		*one;
	t_data		*data;
	pthread_t	time;
	int			i;

	one = global_struct();
	(void)time;
	if (!(data = malloc(sizeof(t_data))))
		return (NULL);
	i = ft_atoi((char *)arg) - 1;
	choose_fork(one, data, i);
	gettimeofday(&data->end, NULL);
	data->time = (data->end.tv_sec * 1000 + data->end.tv_usec) -
					(one->start.tv_sec * 1000 + one->start.tv_usec);
	i = 1;
	while (one->death == 0)
	{
		ft_put_status(one, data, (char *)arg, "THINKING", -1);
		things_bcl(one, data, arg);
		if (one->nb_of_time > 0 && i++ == one->nb_of_time)
			return (NULL);
	}
	return (NULL);
}
