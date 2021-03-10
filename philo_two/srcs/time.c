/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aglorios <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 15:42:11 by aglorios          #+#    #+#             */
/*   Updated: 2021/03/10 15:08:38 by aglorios         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_two.h"

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
	while (i < (time * 10))
	{
		i++;
		if ((get_time() - end) >= time)
			break ;
		usleep(100);
	}
}
