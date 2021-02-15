#include "include/philo_one.h"

int		ft_error(int i)
{
	if (i == 1)
		write(2, "Nbr of arguments ", 17);
	if (i == 2)
		write(2, "Invalid character ", 18);
	if (i == 3)
		write(2, "Not enough Philo ", 17);
	write(2, ": ERROR\n", 8);
	return (0);
}

void	init_struct(t_one *one)
{
	one->nb_of_philo = 0;
	one->t_to_die = 0;
	one->t_to_eat = 0;
	one->t_to_sleep = 0;
	one->nb_of_time = 0;
}

int		get_value(t_one *one, char **argv, int argc)
{
	int i;
	int a;

	i = 0;
	a = 0;
	while (i < (argc - 1) && argv[i++])
	{
		a = 0;
		while (argv[i][a])
			if (!ft_isdigit(argv[i][a++]))
				return (-1);
	}
	one->nb_of_philo = ft_atoi(argv[1]);
	one->t_to_die = ft_atoi(argv[2]);
	one->t_to_eat = ft_atoi(argv[3]);
	one->t_to_sleep = ft_atoi(argv[4]);
	return (1);
}

int		check_value(t_one *one)
{
	if (one->nb_of_philo < 2)
		return (ft_error(3));
	return (1);
}

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

int		ft_thread_create(t_one *one)
{
	pthread_create(&one->philos, NULL, sleeping, &one->t_to_sleep);
	if (pthread_join(one->philos, NULL) != 0 && sleep(one->t_to_die) == 0)
	{
		printf("death\n");
		return (1);
	}
//	eating();
//	pthread_join(one->philos, NULL);
	return (1);
}

int		main(int argc, char **argv)
{
	t_one one;
	
	init_struct(&one);
	if (argc < 5 || argc > 6)
		return (ft_error(1));
	if (get_value(&one, argv, argc) == -1)
		return (ft_error(2));
	if (check_value(&one) == 0)
		return (0);
	if (ft_thread_create(&one) == 0)
		return (0);
	printf("OK\n");
	return (0);
}
