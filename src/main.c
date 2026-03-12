/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arpereir <arpereir@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 02:45:04 by arpereir          #+#    #+#             */
/*   Updated: 2026/03/12 02:53:21 by arpereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	free_all(t_philo *philo)
{
	free(philo->data->forks);
	free(philo->data);
	free(philo);
}

void	*routine(void *arg)
{
	t_philo	*philos;

	philos = (t_philo *)arg;
	pthread_mutex_lock(philos->data->forks);
	printf("philo %i has started\n", philos->id);
	pthread_mutex_unlock(philos->data->forks);
	return (NULL);
}

void	run_threads(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->data->nbr_philo)
	{
		pthread_create(&philo[i].thread, NULL, routine, &philo[i]);
		i++;
	}
	i = 0;
	while (i < philo->data->nbr_philo)
	{
		pthread_join(philo[i].thread, NULL);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_data		*data;
	t_philo		*philo;

	if (argc != 5 && argc != 6)
		return (printf("invalid number of arguments\n"), 1);
	data = malloc(sizeof(t_data));
	if (!data)
		return (1);
	innit_data(data, argc, argv);
	philo = malloc(sizeof(t_philo) * data->nbr_philo);
	if (!philo)
		return (free(data->forks), free(data), 1);
	innit_philo(philo, data);
	run_threads(philo);
	free_all(philo);
	return (0);
}
