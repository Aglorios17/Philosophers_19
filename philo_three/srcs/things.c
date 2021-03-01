/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   things.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aglorios <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 15:42:11 by aglorios          #+#    #+#             */
/*   Updated: 2021/02/26 16:03:35 by aglorios         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_two.h"

void	*eating(void *arg, t_data *data)
{
	t_one	*one;

	one = global_struct();
	sem_wait(data->timing);
	data->live = one->t_to_die + get_time();
	sem_post(data->timing);
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

void	things_bcl(t_one *one, t_data *data, void *arg)
{
	sem_wait(one->sem);
	ft_put_status(data, (char *)arg, NULL, data->fork1);
	sem_wait(one->sem);
	ft_put_status(data, (char *)arg, NULL, data->fork2);
	eating(arg, data);
	sem_post(one->sem);
	sem_post(one->sem);
	sleeping(arg, data);
}

void	*do_time(void *arg)
{
	t_one			*one;
	t_data			*data;
	long int		time;
	struct timeval	end;
	char			*fri;

	one = global_struct();
	data = (t_data *)arg;
	time = 0;
	while (1)
	{
		gettimeofday(&end, NULL);
		time = end.tv_sec * 1000 + end.tv_usec / 1000;
		if (time >= data->live)
		{
			fri = ft_itoa(data->name);
			ft_put_status(data, fri, NULL, -2);
			free(fri);
			sem_post(one->finish);
			return (NULL);
		}
		usleep(5);
	}
	return (NULL);
}
