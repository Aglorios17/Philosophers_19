/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aglorios <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 15:42:11 by aglorios          #+#    #+#             */
/*   Updated: 2019/10/22 16:43:58 by aglorios         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_one.h"

int		ft_thread_alloc(t_one *one)
{
	int	i;

	i = 0;
	if (!(one->philos = malloc(sizeof(pthread_t *) * one->nb_of_philo)))
		return (-1);
	if (!(one->mutex = malloc(sizeof(pthread_mutex_t *) * one->nb_of_philo)))
		return (-1);
	while (i < one->nb_of_philo)
	{
		if (!(one->philos[i] = malloc(sizeof(pthread_t))))
			return (-1);
		if (!(one->mutex[i] = malloc(sizeof(pthread_mutex_t))))
			return (-1);
		pthread_mutex_init(one->mutex[i], NULL);
		i++;
	}
	pthread_mutex_init(&one->write, NULL);
	pthread_mutex_init(&one->finish, NULL);
	pthread_mutex_lock(&one->finish);
	return (1);
}

int		ft_thread_create(t_one *one)
{
	int		i;
	char	*nbp;

	i = 0;
	nbp = NULL;
	if (ft_thread_alloc(one) == -1)
		return (0);
	gettimeofday(&one->start, NULL);
	while (i < one->nb_of_philo)
	{
		nbp = ft_itoa(i + 1);
		pthread_create(one->philos[i++], NULL, do_things, nbp);
	}
	return (1);
}

int		ft_thread_join(t_one *one)
{
	int i;

	i = 0;
	while (i < one->nb_of_philo)
	{
		pthread_detach(*one->philos[i]);
		pthread_mutex_destroy(one->mutex[i++]);
	}
	pthread_mutex_destroy(&one->finish);
	pthread_mutex_destroy(&one->write);
	return (1);
}
