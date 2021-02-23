/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   things.c                                           :+:      :+:    :+:   */
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
	ft_put_status(data, (char *)arg, "EAT", -1);
	pthread_mutex_lock(&data->timing);
	usleep(one->t_to_eat * 1000);
	data->live += one->t_to_die;
	pthread_mutex_unlock(&data->timing);
	return (NULL);
}

void	*sleeping(void *arg, t_data *data)
{
	t_one	*one;

	one = global_struct();
	ft_put_status(data, (char *)arg, "SLEEP", -1);
	usleep(one->t_to_sleep * 1000);
	return (NULL);
}

void	things_bcl(t_one *one, t_data *data, void *arg)
{
	pthread_mutex_lock(one->mutex[data->fork1]);
	ft_put_status(data, (char *)arg, NULL, data->fork1);
	pthread_mutex_lock(one->mutex[data->fork2]);
	ft_put_status(data, (char *)arg, NULL, data->fork2);
	eating(arg, data);
	pthread_mutex_unlock(one->mutex[data->fork1]);
	pthread_mutex_unlock(one->mutex[data->fork2]);
	sleeping(arg, data);
}

void	*do_time(void *arg)
{
	t_one			*one;
	t_data			*data;
	long int		time;
	struct timeval	end;

	one = global_struct();
	data = (t_data *)arg;
	time = 0;
	while (1)
	{
		pthread_mutex_lock(&data->timing);
		gettimeofday(&end, NULL);
		time = end.tv_sec * 1000 + end.tv_usec / 1000;
		if (time >= data->live)
		{
			pthread_mutex_lock(&one->write);
			printf("Philosopher %i est MORT en ||%li||\n",
				data->name, time - data->live);
			exit(1);
		}
		pthread_mutex_unlock(&data->timing);
	}
	return (NULL);
}
