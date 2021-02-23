/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_status.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aglorios <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 15:42:11 by aglorios          #+#    #+#             */
/*   Updated: 2019/10/22 16:43:58 by aglorios         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_one.h"

void	ft_put_status(t_data *data, char *philo, char *put, int i)
{
	char	*nbr;
	t_one	*one;

	nbr = NULL;
	one = global_struct();
	pthread_mutex_lock(&one->write);
	gettimeofday(&data->end, NULL);
	data->time = (data->end.tv_sec * 1000 + data->end.tv_usec / 1000) -
					(one->start.tv_sec * 1000 + one->start.tv_usec / 1000);
	nbr = ft_itoa(data->time);
	write(1, nbr, ft_strlen(nbr));
	write(1, "  Philosopher ||", 16);
	write(1, philo, ft_strlen(philo));
	write(1, "|| ", 3);
	if (i != -1)
	{
		write(1, "has the fork ||", 15);
		nbr = ft_itoa(i);
		write(1, nbr, ft_strlen(nbr));
		write(1, "||", 2);
	}
	else
		write(1, put, ft_strlen(put));
	write(1, "\n", 1);
	pthread_mutex_unlock(&one->write);
}
