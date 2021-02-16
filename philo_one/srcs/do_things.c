#include "../include/philo_one.h"

void	*eating()
{
	t_one	*one;

	one = global_struct();
	printf("eating\n");
	sleep(one->t_to_eat);
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

void	*do_things(void *arg)
{
	int		i;
	t_one	*one;
	int		f;
	pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

	one = global_struct();
	i = one->t_to_sleep;
	f = 0;
	printf("philos |%s| ", (char *)arg);
	pthread_mutex_lock(&lock);
	f = 1;
	pthread_mutex_unlock(&lock);
	if (f == 1)
	{
		eating();
	}
	else
	{
		printf("do things\n");
		sleep(i);
	}
	f = 0;
	pthread_mutex_destroy(&lock);
	return NULL;
}
