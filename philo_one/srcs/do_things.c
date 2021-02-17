#include "../include/philo_one.h"

void	*eating(void *arg)
{
	t_one	*one;

	one = global_struct();
	printf("philos ||%s|| ||EATING||\n\n", (char *)arg);
	sleep(one->t_to_eat);
//	printf("philos ||%s|| finish eating\n\n", (char *)arg);
	return NULL;
}

void	*sleeping(void *arg)
{
	t_one	*one;

	one = global_struct();
	(void)arg;
	printf("philos ||%s|| SLEEPING\n\n", (char *)arg);
	sleep(one->t_to_sleep);
//	printf("philos ||%s|| finish sleeping\n\n", (char *)arg);
	return NULL;
}

void	*thinking(void *arg)
{
	t_one	*one;

	one = global_struct();
	(void)arg;
	printf("philos ||%s|| start thinking\n\n", (char *)arg);
	sleep(one->t_to_die);
	printf("philos ||%s|| finish thinking\n\n", (char *)arg);
	return NULL;
}

int		take_fork(t_one *one, pthread_mutex_t lock, int takefork, int i)
{
//	printf("philos ||%i|| try fork\n\n", i + 1);
	int left;
	int right;

	left = 0;
	right = 0;

	if (i + 1 == one->nb_of_philo)
		right = 0;
	else
		right = i + 1;
	left = i;
	if (i % 2)
	{
		left = right;
		right = i;
	}
	pthread_mutex_lock(&lock);
	if (one->forkette[right] && one->forkette[right] == 1 && 
		one->forkette[left] && one->forkette[left] == 1)
	{
		one->forkette[i] = 2;
		one->forkette[i + 1] = 2;
		takefork = 1;
	}
	else
		takefork = 0;
	pthread_mutex_unlock(&lock);
//	printf("philos ||%i|| finish forking\n\n", i + 1);
	return (takefork);
}

void	*do_things(void *arg)
{
	t_one	*one;
	int		takefork;
	int		i;
//	int		a;
	pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

	takefork = 0;
	one = global_struct();
	i = ft_atoi((char *)arg) - 1; /////// int tab 0 == 1
	printf("philos ||%s|| THINKING\n\n", (char *)arg);
	while (1)
	{
		takefork = take_fork(one, lock, takefork, i);
//		a = 0;
//		printf("-----philos |%s|\n", (char *)arg);
//		while (one->forkette[a])
//			printf("-----before forkette |%i|-----\n", one->forkette[a++]);
	//	printf("---takefork |%i|---\n", takefork);
		if (takefork == 1 || takefork == 2)
		{
//			printf("-----fooooork |%i|\n", one->forkette[i]);
			eating(arg);
			pthread_mutex_lock(&lock);
			one->forkette[i] = 1;
			if (i + 1 == one->nb_of_philo)
				one->forkette[0] = 1;
			else
				one->forkette[i + 1] = 1;
			pthread_mutex_unlock(&lock);
//			printf("-----foooooooork |%i|\n", one->forkette[i]);
			sleeping(arg);
			printf("philos ||%s|| THINKING\n\n", (char *)arg);
		}	
	//	else
	//		thinking(arg);
//		a = 0;
//		printf("-----philos |%s|\n", (char *)arg);
//		while (one->forkette[a])
//			printf("-----after forkette |%i|-----\n", one->forkette[a++]);
	}
	pthread_mutex_destroy(&lock);
	return NULL;
}
