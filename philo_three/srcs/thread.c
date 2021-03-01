/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aglorios <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 15:42:11 by aglorios          #+#    #+#             */
/*   Updated: 2021/03/01 19:34:09 by aglorios         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_three.h"

int		ft_thread_alloc(t_one *one)
{
	sem_unlink("sem");
	sem_unlink("write");
	sem_unlink("finish");
	one->sem = sem_open("sem", O_CREAT, 0660, one->nb_of_philo);
	one->write = sem_open("write", O_CREAT, 0660, 1);
	one->finish = sem_open("finish", O_CREAT, 0660, 1);
	sem_wait(one->finish);
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
			nbp = ft_itoa(i + 1);
			do_things(nbp);
		}
		i++;
	}
	i = 0;
	while (i < one->nb_of_philo)
		waitpid(myphiphi[i++], 0, 0);
	return (1);
}

int		ft_thread_join(t_one *one)
{
//	sem_post(one->sem);
//	sem_post(one->finish);
//	sem_post(one->write);
	sem_close(one->sem);
	sem_close(one->finish);
	sem_close(one->write);
	return (1);
}
