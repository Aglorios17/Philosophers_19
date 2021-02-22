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

typedef struct		s_philo_one
{
	int				nb_of_philo;
	int				t_to_die;
	int				t_to_eat;
	int				t_to_sleep;
	int				nb_of_time;
	pthread_t		**philos;
	pthread_t		time;
	pthread_mutex_t	**mutex;
	pthread_mutex_t	write;
	int				*forkette;
	struct timeval	start;
}					t_one;

typedef struct		s_data
{
	int				fork1;
	int				fork2;
	struct timeval	end;
	int				time;
}					t_data;

t_one				*global_struct(void);
int					ft_error(int i);
void				init_struct(t_one *one);
int					get_value(t_one *one, char **argv, int argc);
int					check_value(t_one *one);

int					ft_thread_alloc(t_one *one);
void				*do_time(void *arg);
int					ft_thread_create(t_one *one);
int					ft_thread_join(t_one *one);

void				*do_things(void *arg);
void				*eating(void *arg, t_data *data);
void				*sleeping(void *arg, t_data *data);
void				ft_put_status(t_one *one, t_data *data, char *philo, char *put, int i);

int					ft_atoi(const char *str);
int					ft_isdigit(int c);
char				*ft_itoa(int n);
char				*ft_strdup(const char *src);
size_t				ft_strlen(const char *str);

#endif
