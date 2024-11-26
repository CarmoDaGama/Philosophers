/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgama <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 08:57:00 by cgama             #+#    #+#             */
/*   Updated: 2024/11/05 08:57:02 by cgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_args(t_philo *philo, char **argv)
{
	philo->num_of_philos = ft_atoi(argv[1]);
	philo->time_to_die = ft_atoi(argv[2]);
	philo->time_to_eat = ft_atoi(argv[3]);
	philo->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		philo->num_times_eat = ft_atoi(argv[5]);
	else
		philo->num_times_eat = -1;
}

void	init_philos(t_philo *philos, t_process *process, pthread_mutex_t *forks,
	char **argv)
{
	int	i;

	i = 0;
	while (i < ft_atoi(argv[1]))
	{
		philos[i].id = i + 1;
		philos[i].eating = 0;
		philos[i].meals_eaten = 0;
		init_args(&philos[i], argv);
		philos[i].start_time = get_current_time();
		philos[i].last_meal = get_current_time();
		philos[i].write_lock = &process->write_lock;
		philos[i].dead_lock = &process->dead_lock;
		philos[i].meal_lock = &process->meal_lock;
		philos[i].dead = &process->dead_flag;
		philos[i].l_fork = &forks[i];
		if (i == 0)
			philos[i].r_fork = &forks[philos[i].num_of_philos - 1];
		else
			philos[i].r_fork = &forks[i - 1];
		i++;
	}
}

void	init_forks(pthread_mutex_t *forks, int num_philo)
{
	int	i;

	i = 0;
	while (i < num_philo)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
}

void	init_process(t_process *process, t_philo *philos)
{
	process->dead_flag = 0;
	process->philos = philos;
	pthread_mutex_init(&process->write_lock, NULL);
	pthread_mutex_init(&process->dead_lock, NULL);
	pthread_mutex_init(&process->meal_lock, NULL);
}
