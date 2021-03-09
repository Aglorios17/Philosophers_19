/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_things.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aglorios <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 15:42:11 by aglorios          #+#    #+#             */
/*   Updated: 2021/03/09 16:16:19 by aglorios         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_two.h"

void	init_do_things(t_one *one, t_data *data, char *arg, int i)
{
	sem_unlink("timing");
	data->timing = sem_open("timing", O_CREAT, 0660, 1);
	data->timer = 0;
	data->name = ft_atoi(arg);
	(void)i;
	gettimeofday(&data->end, NULL);
	data->live = (data->end.tv_sec * 1000 + data->end.tv_usec / 1000)
					+ one->t_to_die;
}

void	all_eat(t_one *one, t_data *data)
{
	if (one->all_eat == one->nb_of_philo - 1)
	{
		sem_close(data->timing);
		pthread_detach(data->timer);
		sem_wait(one->write);
		sem_post(one->finish);
	}
	else
	{
		sem_close(data->timing);
		pthread_detach(data->timer);
	}
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
		{
			sem_wait(one->write);
			one->all_eat++;
			sem_post(one->write);
		}
		if (one->all_eat == one->nb_of_philo - 1)
			break ;
	}
	all_eat(one, data);
	return (NULL);
}
