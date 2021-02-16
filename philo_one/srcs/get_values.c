#include "../include/philo_one.h"

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
