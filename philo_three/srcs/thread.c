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

#include "../include/philo_three.h"

int		ft_thread_alloc(t_one *one)
{
	int	i;

	i = 0;
	if (!(one->philos = malloc(sizeof(pid_t *) * one->nb_of_philo)))
		return (-1);
	while (i < one->nb_of_philo)
	{
		if (!(one->philos[i] = malloc(sizeof(pid_t))))
			return (-1);
		i++;
	}
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

	i = 0;
	nbp = NULL;
	if (ft_thread_alloc(one) == -1)
		return (0);
	gettimeofday(&one->start, NULL);
	while (i < one->nb_of_philo)
	{
		nbp = ft_itoa(i + 1);
		if ((*one->philos[i] = fork()) == -1)
			return (0);
		if (*one->philos[i] == 0)
			do_things(nbp);
		else
			waitpid(*one->philos[i], NULL, 0);
		i++;
	}
	return (1);
}

int		ft_thread_join(t_one *one)
{
	int i;

	i = 0;
	while (i < one->nb_of_philo)
		exit(0);
	sem_close(one->sem);
	sem_close(one->finish);
	sem_close(one->write);
	return (1);
}
