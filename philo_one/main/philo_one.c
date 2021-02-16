#include "../include/philo_one.h"

int		ft_thread_alloc(t_one *one)
{
	int i;

	i = 0;
	one->philos = malloc(sizeof(pthread_t *));
	while (i < one->nb_of_philo)
		one->philos[i++] = malloc(sizeof(pthread_t));
	return (1);
}

int		ft_thread_create(t_one *one)
{
	int i;
	char *nbp;

	i = 0;
	nbp = NULL;
	if (ft_thread_alloc(one) == -1)
		return (0);
	while (i < one->nb_of_philo)
	{
		nbp = ft_itoa(i + 1); ////////////////////////////////////// free after thread_join	
		pthread_create(one->philos[i++], NULL, do_things, nbp);
	}
	return (1);
}

int		ft_thread_join(t_one *one)
{
	int i;

	i = 0;
	while (i < one->nb_of_philo)
	{
		if (pthread_join(*one->philos[i++], NULL) != 0)
		{
			printf("death\n");
			return (1);
		}
	}
	return (1);
}

t_one	*global_struct(void)
{
	static t_one	one;
	return (&one);
}

int		main(int argc, char **argv)
{
	t_one *one;
	

	one = global_struct();
	init_struct(one);
	if (argc < 5 || argc > 6)
		return (ft_error(1));
	if (get_value(one, argv, argc) == -1)
		return (ft_error(2));
	if (check_value(one) == 0)
		return (0);
	if (ft_thread_create(one) == 0)
		return (0);
	if (ft_thread_join(one) == 0)
		return (0);
	printf("OK\n");
	return (0);
}
