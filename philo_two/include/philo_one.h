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
	pthread_t		**philos;
	pthread_mutex_t	**mutex;
	pthread_mutex_t	write;
	pthread_mutex_t	finish;
	struct timeval	start;
	int				nb_of_philo;
	int				t_to_die;
	int				t_to_eat;
	int				t_to_sleep;
	int				nb_of_time;
	int				death;
}					t_one;

typedef struct		s_data
{
	pthread_t		timer;
	pthread_mutex_t	timing;
	struct timeval	end;
	int				name;
	int				fork1;
	int				fork2;
	long int		time;
	long int		live;
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
void				init_do_things(t_one *one, t_data *data, char *arg, int i);
void				things_bcl(t_one *one, t_data *data, void *arg);
void				*eating(void *arg, t_data *data);
void				*sleeping(void *arg, t_data *data);
void				ft_put_status(t_data *data, char *philo,
						char *put, int i);
void				meal_count(t_one *one, t_data *data);

void				my_sleep(long int time);
long				get_time(void);
int					ft_atoi(const char *str);
int					ft_isdigit(int c);
char				*ft_itoa(int n);
char				*ft_strdup(const char *src);
size_t				ft_strlen(const char *str);
char				*ft_strjoin(char const *s1, char const *s2);

#endif
