/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aglorios <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 12:52:08 by aglorios          #+#    #+#             */
/*   Updated: 2020/03/04 12:53:38 by aglorios         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct	s_philo_one
{
	int 			nb_of_philo;
	int				t_to_die;
	int				t_to_eat;
	int				t_to_sleep;
	int				nb_of_time;
	pthread_t		**philos;
	pthread_mutex_t	**mutex;
	int				*forkette;
}				t_one;

/////////////// INIT MAIN //////////////
t_one	*global_struct(void);
int		ft_error(int i);
void	init_struct(t_one *one);
int		get_value(t_one *one, char **argv, int argc);
int		check_value(t_one *one);

/////////////// DO_THINGS //////////////
void	*do_things(void *arg);
void	*eating();
void	*sleeping(void *arg);
void	*thinking(void *arg);
///////////////    UTILS  //////////////
int		ft_atoi(const char *str);
int		ft_isdigit(int c);
char	*ft_itoa(int n);
char	*ft_strdup(const char *src);
size_t	ft_strlen(const char *str);

#endif
