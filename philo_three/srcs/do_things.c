/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_things.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aglorios <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 15:42:11 by aglorios          #+#    #+#             */
/*   Updated: 2021/02/25 13:54:37 by aglorios         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_three.h"

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
		ft_put_status(data, (char *)arg, "THINK", -1);
		things_bcl(one, data, arg);
		if (one->nb_of_time > 0 && i++ == one->nb_of_time)
		{
			sem_post(one->finish);
			pthread_detach(data->timer);
			sem_close(data->timing);
			return (NULL);
		}
	}
	pthread_detach(data->timer);
	sem_close(data->timing);
	return (NULL);
}
