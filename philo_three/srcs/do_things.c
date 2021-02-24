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

void	init_do_things(t_one *one, t_data *data, char *arg, int i)
{
	pthread_mutex_init(&data->timing, NULL);
	data->timer = 0;
	data->name = ft_atoi(arg);
	i = ft_atoi(arg) - 1;
	choose_fork(one, data, i);
	gettimeofday(&data->end, NULL);
	data->live = (data->end.tv_sec * 1000 + data->end.tv_usec / 1000)
					+ one->t_to_die;
}

void	*do_things(void *arg)
{
	t_one		*one;
	t_data		*data;
	int			i;

	one = global_struct();
	i = 0;
	if (!(data = malloc(sizeof(t_data))))
		return (NULL);
	init_do_things(one, data, arg, i);
	i = 1;
	pthread_create(&data->timer, NULL, do_time, data);
	while (one->death == 0)
	{
		ft_put_status(data, (char *)arg, "THINK", -1);
		things_bcl(one, data, arg);
		if (one->nb_of_time > 0 && i++ == one->nb_of_time)
		{
			pthread_detach(data->timer);
			return (NULL);
		}
	}
	pthread_detach(data->timer);
	exit(1); /////////////////////// need return
	return (NULL);
}
