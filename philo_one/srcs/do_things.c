#include "../include/philo_one.h"

void	*eating(void *arg)
{
	t_one	*one;

	one = global_struct();
	printf("--philos |%s| ||start eating||\n", (char *)arg);
	sleep(one->t_to_eat);
	printf("--philos |%s| finish eating\n", (char *)arg);
	return NULL;
}

void	*sleeping(void *arg)
{
	t_one	*one;

	one = global_struct();
	printf("-philos |%s| start sleeping\n", (char *)arg);
	sleep(one->t_to_sleep);
	printf("-philos |%s| finish sleeping\n", (char *)arg);
	return NULL;
}

void	*thinking(void *arg)
{
	t_one	*one;

	one = global_struct();
	printf("-philos |%s| start thinking\n", (char *)arg);
	sleep(one->t_to_die);
	printf("-philos |%s| finish thinking\n", (char *)arg);
	return NULL;
}

void	*do_things(void *arg)
{
	t_one	*one;
	int		takefork;
	int		i;
	pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

	printf("\n");
	takefork = 0;
	one = global_struct();
	i = ft_atoi((char *)arg);
	pthread_mutex_lock(&lock);
	if (one->forkette[i] && one->forkette[i + 1] && 
		one->forkette[i] == 1 && one->forkette[i + 1] == 1)
	{
		one->forkette[i] = 2;
		one->forkette[i + 1] = 2;
		takefork = 1;
	}
	pthread_mutex_unlock(&lock);
	i = 0;
//	printf("-----philos |%s|\n", (char *)arg);
//	while (one->forkette[i])
//		printf("-----forkette |%i|-----\n", one->forkette[i++]);
//	printf("---takefork |%i|---\n", takefork);
	if (takefork == 1)
	{	
		eating(arg);
		sleeping(arg);
	}
	else
		thinking(arg);
	one->forkette[i] = 1;
	one->forkette[i + 1] = 1;
	pthread_mutex_destroy(&lock);
	return NULL;
}
