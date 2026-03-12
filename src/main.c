/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arpereir <arpereir@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 02:45:04 by arpereir          #+#    #+#             */
/*   Updated: 2026/03/12 03:15:54 by arpereir         ###   ########.fr       */
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
	t_philo	*philo;

	philo = (t_philo *)arg;
	printf("philo %i has started\n", philo->id);
	printf("left fork = %p\n", (void*)philo->left_fork);
	printf("right fork = %p\n\n", (void*)philo->right_fork);
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
	init_data(data, argc, argv);
	philo = malloc(sizeof(t_philo) * data->nbr_philo);
	if (!philo)
		return (free(data->forks), free(data), 1);
	init_philo(philo, data);
	run_threads(philo);
	free_all(philo);
	return (0);
}
