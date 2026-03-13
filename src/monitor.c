/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arpereir <arpereir@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 20:13:25 by arpereir          #+#    #+#             */
/*   Updated: 2026/03/13 05:27:05 by arpereir         ###   ########.fr       */
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

void	check_meals_eaten(t_philo *philo, int *full)
{
	if (philo->data->must_eat_count != -1)
	{
		if (philo->meals_eaten >= philo->data->must_eat_count)
			*full += 1;
		if (*full == philo->data->nbr_philo)
			set_dead(philo);
	}
}

void	monitor(t_philo *philo)
{
	int		i;
	int		full;
	long	time_since_meal;

	i = 0;
	while (!philo[0].data->someone_died )
	{
		i = 0;
		full = 0;
		while (i < philo[0].data->nbr_philo)
		{
			pthread_mutex_lock(&philo->data->meal_lock);
			check_meals_eaten(&philo[i], &full);
			time_since_meal = get_time_in_ms() - philo[i].last_meal;
			pthread_mutex_unlock(&philo->data->meal_lock);
			if (time_since_meal > philo[0].data->time_to_die)
			{
				set_dead(philo);
				print_status(&philo[i], "died");
				return ;
			}
			i++;
		}
		usleep(1000);
	}
}
