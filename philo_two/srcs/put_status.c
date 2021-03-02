/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_status.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aglorios <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 15:42:11 by aglorios          #+#    #+#             */
/*   Updated: 2021/02/26 16:04:20 by aglorios         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_two.h"

void	time_status(t_data *data, char *philo)
{
	t_one	*one;
	char	*fri;

	one = global_struct();
	fri = NULL;
	gettimeofday(&data->end, NULL);
	data->time = (data->end.tv_sec * 1000 + data->end.tv_usec / 1000) -
					(one->start.tv_sec * 1000 + one->start.tv_usec / 1000);
	fri = ft_itoa(data->time);
	write(1, fri, ft_strlen(fri));
	free(fri);
	write(1, " Philosopher ", 13);
	write(1, philo, ft_strlen(philo));
	write(1, " ", 1);
}

void	fork_put(int i)
{
	write(1, "has taken a fork ", 17);
	(void)i;
}

void	choose_status(char *put, int i)
{
	t_one	*one;

	one = global_struct();
	if (i != -1 && i != -2)
		fork_put(i);
	else if (i == -1)
		write(1, put, ft_strlen(put));
	else
	{
		write(1, "died", 4);
		one->death = 1;
	}
}

void	ft_put_status(t_data *data, char *philo, char *put, int i)
{
	t_one	*one;

	one = global_struct();
	sem_wait(one->write);
	if (one->death == 1)
	{
		sem_post(one->write);
		return ;
	}
	time_status(data, philo);
	choose_status(put, i);
	write(1, "\n", 1);
	sem_post(one->write);
}
