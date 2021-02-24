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

long	get_time(void)
{
	struct timeval	tp;
	long			milliseconds;

	gettimeofday(&tp, NULL);
	milliseconds = tp.tv_sec * 1000;
	milliseconds += tp.tv_usec / 1000;
	return (milliseconds);
}

void	my_sleep(long int time)
{
	long int	i;
	long int	t;

	i = 0;
	t = get_time();
	while (i < (time * 20))
	{
		i++;
		if ((get_time() - t) >= time)
			break ;
		usleep(50);
	}
}

void	ft_put_status(t_data *data, char *philo, char *put, int i)
{
	char	*nbr;
	char	*str;
	t_one	*one;

	nbr = NULL;
	str = NULL;
	one = global_struct();
	pthread_mutex_lock(&one->write);
	gettimeofday(&data->end, NULL);
	data->time = (data->end.tv_sec * 1000 + data->end.tv_usec / 1000) -
					(one->start.tv_sec * 1000 + one->start.tv_usec / 1000);
	str = ft_itoa(data->time);
	str = ft_strjoin(str, "  Philosopher ||");
	str = ft_strjoin(str, philo);
	str = ft_strjoin(str, "|| ");
	if (i != -1)
	{
		str = ft_strjoin(str, "has the fork ||");
		nbr = ft_itoa(i);
		str = ft_strjoin(str, nbr);
		str = ft_strjoin(str, "||");
	}
	else
		str = ft_strjoin(str, put);
	str = ft_strjoin(str, "\n");
	write(1, str, ft_strlen(str));
	pthread_mutex_unlock(&one->write);
}
