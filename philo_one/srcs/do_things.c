#include "../include/philo_one.h"

void	*eating()
{
	int i;

	i = 0;
	while (i++ < 10)
	{
		sleep(2);
		printf("eating\n");
	}
	return NULL;
}

void	*sleeping(void *arg)
{
	int *i;

	i = (int *)arg;
	printf("sleeping\n");
	sleep(*i);
	return NULL;
}

void	*thinking(t_one *one)
{
	printf("thinking\n");
	sleep(one->t_to_sleep);
	return NULL;
}
