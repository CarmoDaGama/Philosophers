/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threading.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgama <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 08:56:37 by cgama             #+#    #+#             */
/*   Updated: 2024/11/08 10:50:01 by cgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	philo_dead(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (*philo->dead == 1)
		return (pthread_mutex_unlock(philo->dead_lock), true);
	pthread_mutex_unlock(philo->dead_lock);
	return (false);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		ft_usleep(1);
	while (!philo_dead(philo))
	{
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (arg);
}

int	thread_create(t_process *process, pthread_mutex_t *forks)
{
	pthread_t	observer;
	int			i;

	if (pthread_create(&observer, NULL, &observing, process->philos) != 0)
		mutexes_destroy("Thread creation error", process, forks);
	i = 0;
	while (i < process->philos->num_of_philos)
	{
		if (pthread_create(&process->philos[i].thread, NULL, &routine,
				&process->philos[i]) != 0)
			mutexes_destroy("Thread creation error", process, forks);
		i++;
	}
	i = 0;
	if (pthread_join(observer, NULL) != 0)
		mutexes_destroy("Thread join error", process, forks);
	while (i < process->philos[0].num_of_philos)
	{
		if (pthread_join(process->philos[i].thread, NULL) != 0)
			mutexes_destroy("Thread join error", process, forks);
		i++;
	}
	return (0);
}
