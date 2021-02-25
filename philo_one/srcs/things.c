/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   things.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aglorios <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 15:42:11 by aglorios          #+#    #+#             */
/*   Updated: 2021/02/25 15:49:06 by aglorios         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_one.h"

void	*eating(void *arg, t_data *data)
{
	t_one	*one;

	one = global_struct();
	pthread_mutex_lock(&data->timing);
	data->live = one->t_to_die + get_time();
	pthread_mutex_unlock(&data->timing);
	ft_put_status(data, (char *)arg, "EAT", -1);
	my_sleep(one->t_to_eat);
	return (NULL);
}

void	*sleeping(void *arg, t_data *data)
{
	t_one	*one;

	one = global_struct();
	gettimeofday(&data->end, NULL);
	data->time = (data->end.tv_sec * 1000 + data->end.tv_usec / 1000) -
					(one->start.tv_sec * 1000 + one->start.tv_usec / 1000);
	ft_put_status(data, (char *)arg, "SLEEP", -1);
	my_sleep(one->t_to_sleep);
	return (NULL);
}

void	meal_count(t_one *one, t_data *data)
{
//	printf("\ndata->meal || %i ||\n", data->meal);
//	printf("\nphilos || %i ||\n", one->nb_of_philo);
//	printf("\nmeal * philo || %i ||\n", data->meal * one->nb_of_philo);
//	printf("\nok");
//	pthread_mutex_unlock(&one->finish);
	usleep(500);
	while (1)
	{
		if ((one->count / one->nb_of_philo) == data->meal)
		{
//			pthread_mutex_lock(&one->write);
//			printf("Philo nb || %i ||\n", data->name);
//			printf("one->count || %i ||\n", one->count);
//			printf("data->meal || %i ||\n", data->meal);
//			printf("nb of philos || %i ||\n", one->nb_of_philo);
//			printf("meal * philo || %i ||\n", data->meal * one->nb_of_philo);
//			pthread_mutex_unlock(&one->write);
//			exit(1);
			break;
		}
//		pthread_mutex_unlock(&one->finish);
//			exit(1);
		usleep(5);
	}
//	printf("\nok2\n");
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
//	pthread_mutex_lock(&one->eat);
//	one->count++;
//	pthread_mutex_unlock(&one->eat);
//	data->meal++;
	sleeping(arg, data);
//	meal_count(one, data);
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
	data->meal = 0;
	while (1)
	{
		gettimeofday(&end, NULL);
		time = end.tv_sec * 1000 + end.tv_usec / 1000;
		if (time >= data->live)
		{
			pthread_mutex_lock(&one->write);
			printf("Philosopher %i est MORT en ||%li||\n",
				data->name, (end.tv_sec * 1000 + end.tv_usec / 1000) -
					(one->start.tv_sec * 1000 + one->start.tv_usec / 1000));
			pthread_mutex_unlock(&one->finish);
			one->death = 1;
			return (NULL);
		}
		usleep(5);
	}
	return (NULL);
}
