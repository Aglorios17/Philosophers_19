/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aglorios <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 15:42:11 by aglorios          #+#    #+#             */
/*   Updated: 2021/03/10 15:24:56 by aglorios         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_three.h"

int		ft_thread_alloc(t_one *one)
{
	int i;

	i = 0;
	sem_unlink("sem");
	sem_unlink("write");
	sem_unlink("finish");
	sem_unlink("sem_eat");
	one->sem = sem_open("sem", O_CREAT, 0660, one->nb_of_philo);
	one->sem_eat = sem_open("sem_eat", O_CREAT, 0660, one->nb_of_philo);
	one->write = sem_open("write", O_CREAT, 0660, 1);
	one->finish = sem_open("finish", O_CREAT, 0660, 1);
	sem_wait(one->finish);
	while (i < one->nb_of_philo)
	{
		sem_wait(one->sem_eat);
		i++;
	}
	return (1);
}

int		ft_thread_create(t_one *one)
{
	int		i;
	char	*nbp;
	pid_t	myphiphi[201];

	i = 0;
	nbp = NULL;
	if (ft_thread_alloc(one) == -1)
		return (0);
	gettimeofday(&one->start, NULL);
	while (i < one->nb_of_philo)
	{
		if ((myphiphi[i] = fork()) == -1)
			return (0);
		if (myphiphi[i] == 0)
		{
			if (!(nbp = ft_itoa(i + 1)))
				return (0);
			do_things(nbp);
		}
		i++;
	}
	i = 0;
	while (i < one->nb_of_philo)
	{
		sem_wait(one->sem_eat);
		i++;
	}
	i = 0;
	while (i < one->nb_of_philo)
		waitpid(myphiphi[i++], NULL, 0);
	while (i < one->nb_of_philo)
	{
		sem_wait(one->sem);
		sem_post(one->sem);
	}
	sem_post(one->finish);
	exit(0);
	return (1);
}

int		ft_thread_join(t_one *one)
{
	sem_close(one->sem);
	sem_close(one->sem_eat);
	sem_close(one->finish);
	sem_close(one->write);
	return (1);
}
