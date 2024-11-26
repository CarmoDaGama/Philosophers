/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   observer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgama <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 11:08:51 by cgama             #+#    #+#             */
/*   Updated: 2024/11/05 11:08:53 by cgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	write_msg(char *str, t_philo *philo, int id)
{
	size_t	time;

	pthread_mutex_lock(philo->write_lock);
	time = get_current_time() - philo->start_time;
	if (!philo_dead(philo))
		printf("%zu %d %s\n", time, id, str);
	pthread_mutex_unlock(philo->write_lock);
}

bool	no_ate(t_philo *philo, size_t time_to_die)
{
	pthread_mutex_lock(philo->meal_lock);
	if (get_current_time() - philo->last_meal >= time_to_die
		&& philo->eating == 0)
		return (pthread_mutex_unlock(philo->meal_lock), true);
	pthread_mutex_unlock(philo->meal_lock);
	return (false);
}

bool	any_no_ate(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos[0].num_of_philos)
	{
		if (no_ate(&philos[i], philos[i].time_to_die))
		{
			write_msg("did", &philos[i], philos[i].id);
			pthread_mutex_lock(philos[0].dead_lock);
			*philos->dead = 1;
			pthread_mutex_unlock(philos[0].dead_lock);
			return (true);
		}
		i++;
	}
	return (false);
}

bool	is_all_ate(t_philo *philos)
{
	int	i;
	int	f_eating;

	i = 0;
	f_eating = 0;
	if (philos[0].num_times_eat == -1)
		return (false);
	while (i < philos[0].num_of_philos)
	{
		pthread_mutex_lock(philos[i].meal_lock);
		if (philos[i].meals_eaten >= philos[i].num_times_eat)
			f_eating++;
		pthread_mutex_unlock(philos[i].meal_lock);
		i++;
	}
	if (f_eating == philos[0].num_of_philos)
	{
		pthread_mutex_lock(philos[0].dead_lock);
		*philos[0].dead = 1;
		pthread_mutex_unlock(philos[0].dead_lock);
		return (true);
	}
	return (false);
}

void	*observing(void *args)
{
	t_philo	*philos;

	philos = (t_philo *)args;
	while (1)
		if (any_no_ate(philos) || is_all_ate(philos))
			break ;
	return (args);
}
