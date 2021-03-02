/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_things.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aglorios <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 15:42:11 by aglorios          #+#    #+#             */
/*   Updated: 2021/03/02 19:04:12 by aglorios         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_one.h"

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
		if (data->name == one->nb_of_philo && data->name % 2 == 0)
		{
			data->fork2 = data->fork1;
			data->fork1 = i;
		}
		else
		{
			data->fork1 = data->fork1;
			data->fork2 = i;
		}
	}
}

void	init_do_things(t_one *one, t_data *data, char *arg, int i)
{
	pthread_mutex_init(&data->timing, NULL);
	data->timer = 0;
	data->name = ft_atoi(arg);
	i = ft_atoi(arg) - 1;
	if (i % 2)
		usleep(500);
	choose_fork(one, data, i);
	gettimeofday(&data->end, NULL);
	data->live = (data->end.tv_sec * 1000 + data->end.tv_usec / 1000)
					+ one->t_to_die;
}

void	all_eat(t_one *one, t_data *data)
{
	pthread_mutex_lock(&one->write);
	one->all_eat++;
	pthread_mutex_unlock(&one->write);
	pthread_mutex_lock(&data->timing);
	data->live = 1000000 + get_time();
	pthread_mutex_unlock(&data->timing);
	while (1)
	{
		if (one->all_eat == one->nb_of_philo - 1)
			break ;
		usleep(5);
	}
	pthread_detach(data->timer);
	pthread_mutex_destroy(&data->timing);
	pthread_mutex_unlock(&one->finish);
}

void	*do_things(void *arg)
{
	t_one		*one;
	t_data		*data;
	int			i;

	one = global_struct();
	i = 1;
	if (!(data = malloc(sizeof(t_data))))
		return (NULL);
	init_do_things(one, data, arg, 0);
	pthread_create(&data->timer, NULL, do_time, data);
	while (one->death == 0)
	{
		ft_put_status(data, (char *)arg, "is thinking", -1);
		things_bcl(one, data, arg);
		if (one->nb_of_time > 0 && i++ == one->nb_of_time)
			break ;
		choose_fork(one, data, data->name - 1);
	}
	all_eat(one, data);
	return (NULL);
}
