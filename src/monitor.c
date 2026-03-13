/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arpereir <arpereir@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 20:13:25 by arpereir          #+#    #+#             */
/*   Updated: 2026/03/13 02:01:56 by arpereir         ###   ########.fr       */
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

void	monitor(t_philo *philo)
{
	int		i;
	long	time_since_meal;

	i = 0;
	while (!philo[0].data->someone_died)
	{
		i = 0;
		while (i < philo[0].data->nbr_philo)
		{
			pthread_mutex_lock(&philo->data->meal_lock);
			time_since_meal = get_time_in_ms() - philo[i].last_meal;
			pthread_mutex_unlock(&philo->data->meal_lock);
			if (time_since_meal > philo[0].data->time_to_die)
			{
				set_dead(philo);
				print_status(philo, "died");
				return ;
			}
			i++;
		}
		usleep(1000);
	}
}
