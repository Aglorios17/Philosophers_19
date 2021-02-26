/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_status.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aglorios <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 15:42:11 by aglorios          #+#    #+#             */
/*   Updated: 2021/02/25 15:43:08 by aglorios         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_one.h"

long	get_time(void)
{
	struct timeval	end;
	long			ms;

	gettimeofday(&end, NULL);
	ms = end.tv_sec * 1000;
	ms += end.tv_usec / 1000;
	return (ms);
}

void	my_sleep(long int time)
{
	long int	i;
	long int	end;

	i = 0;
	end = get_time();
	while (i < (time * 20))
	{
		i++;
		if ((get_time() - end) >= time)
			break ;
		usleep(50);
	}
}

void	ft_put_status(t_data *data, char *philo, char *put, int i)
{
	char	*nbr;
	char	*str;
	char	*fri;
	t_one	*one;

	nbr = NULL;
	str = NULL;
	fri = NULL;
	one = global_struct();
	pthread_mutex_lock(&one->write);
	if (one->death == 1)
	{
		pthread_mutex_unlock(&one->write);
		return ;
	}
	gettimeofday(&data->end, NULL);
	data->time = (data->end.tv_sec * 1000 + data->end.tv_usec / 1000) -
					(one->start.tv_sec * 1000 + one->start.tv_usec / 1000);

	fri = ft_itoa(data->time);
	str = ft_strjoin(fri, " Philosopher ");
	free(fri);
	fri = str;
	str = ft_strjoin(str, philo);
	free(fri);
	fri = str;
	str = ft_strjoin(str, " ");
	free(fri);
	if (i != -1 && i != -2)
	{
		fri = str;
		str = ft_strjoin(str, "has fork ");
		free(fri);
		nbr = ft_itoa(i);
		fri = str;
		str = ft_strjoin(str, nbr);
		free(fri);
		free(nbr);
	}
	else if (i == -1)
	{
		fri = str;
		str = ft_strjoin(str, put);
		free(fri);
	}
	else
	{
		fri = str;
		str = ft_strjoin(str, "est mort");
		free(fri);
	}
	fri = str;
	str = ft_strjoin(str, "\n");
	free(fri);
	write(1, str, ft_strlen(str));
	pthread_mutex_unlock(&one->write);
}
