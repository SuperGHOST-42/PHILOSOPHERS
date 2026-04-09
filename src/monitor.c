/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arpereir <arpereir@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 20:13:25 by arpereir          #+#    #+#             */
/*   Updated: 2026/04/09 20:05:30 by arpereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	is_dead(t_philo *philo)
{
	int	dead;

	pthread_mutex_lock(&philo->data->dead_lock);
	dead = philo->data->someone_died;
	pthread_mutex_unlock(&philo->data->dead_lock);
	return (dead);
}

static void	set_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->dead_lock);
	philo->data->someone_died = 1;
	pthread_mutex_unlock(&philo->data->dead_lock);
}

static int	check_meals_eaten(t_philo *philo, long *full)
{
	if (philo->data->must_eat_count == -1)
		return (0);
	if (philo->meals_eaten >= philo->data->must_eat_count)
		(*full)++;
	if (*full == philo->data->nbr_philo)
		return (1);
	return (0);
}

static int	check_philo_state(t_philo *philo, long *full)
{
	long	time_since_meal;

	pthread_mutex_lock(&philo->data->meal_lock);
	if (check_meals_eaten(philo, full) == 1)
	{
		pthread_mutex_unlock(&philo->data->meal_lock);
		set_dead(philo);
		return (1);
	}
	time_since_meal = get_time_in_ms() - philo->last_meal;
	pthread_mutex_unlock(&philo->data->meal_lock);
	if (time_since_meal >= philo->data->time_to_die)
	{
		set_dead(philo);
		print_status(philo, "died");
		return (1);
	}
	return (0);
}

void	monitor(t_philo *philo)
{
	int		i;
	long	full;

	while (!is_dead(philo))
	{
		i = 0;
		full = 0;
		while (i < philo->data->nbr_philo)
		{
			if (check_philo_state(&philo[i], &full) == 1)
				return ;
			i++;
		}
		usleep(1000);
	}
}
