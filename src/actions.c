/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arpereir <arpereir@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 14:48:54 by arpereir          #+#    #+#             */
/*   Updated: 2026/03/12 15:22:55 by arpereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	eat(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		printf("philo %i has taken a right fork\n", philo->id);
		pthread_mutex_lock(philo->left_fork);
		printf("philo %i has taken a left fork\n", philo->id);
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		printf("philo %i has taken a left fork\n", philo->id);
		pthread_mutex_lock(philo->right_fork);
		printf("philo %i has taken a right fork\n", philo->id);
	}
	print_msg(philo, "is eating\n");
	usleep(philo->data->time_to_eat * 1000);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	philo_sleep(t_philo *philo)
{
	print_msg(philo, "is sleeping\n");
	usleep(philo->data->time_to_sleep * 1000);
}

void	think(t_philo *philo)
{
	print_msg(philo, "is thinking\n");
}