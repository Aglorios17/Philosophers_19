#include "../include/philo_one.h"

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
