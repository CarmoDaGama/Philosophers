/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgama <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 08:56:22 by cgama             #+#    #+#             */
/*   Updated: 2024/11/05 08:56:25 by cgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdbool.h>

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				eating;
	int				meals_eaten;
	size_t			last_meal;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			start_time;
	int				num_of_philos;
	int				num_times_eat;
	int				*dead;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*meal_lock;
}					t_philo;

typedef struct s_process
{
	int				dead_flag;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	write_lock;
	t_philo			*philos;

}					t_process;

int					ft_strlen(char *str);
int					ft_atoi(char *str);
void				mutexes_destroy(char *str,
						t_process *process, pthread_mutex_t *forks);
int					ft_usleep(size_t milliseconds);
size_t				get_current_time(void);
void				init_process(t_process *process, t_philo *philos);
void				init_forks(pthread_mutex_t *forks, int num_philo);
void				init_philos(t_philo *philos,
						t_process *process, pthread_mutex_t *forks,
						char **argv);
void				init_args(t_philo *philo, char **argv);
bool				philo_dead(t_philo *philo);
void				*routine(void *pointer);
int					thread_create(t_process *process, pthread_mutex_t *forks);
void				*observing(void *args);
bool				is_all_ate(t_philo *philos);
bool				any_no_ate(t_philo *philos);
void				write_msg(char *str, t_philo *philo, int id);
void				thinking(t_philo *philo);
void				sleeping(t_philo *philo);
void				eating(t_philo *philo);
#endif
