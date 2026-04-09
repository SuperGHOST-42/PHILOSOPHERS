/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arpereir <arpereir@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 02:45:04 by arpereir          #+#    #+#             */
/*   Updated: 2026/04/09 20:42:11 by arpereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->nbr_philo == (long)1)
	{
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, "has taken a fork");
		ft_usleep(philo->data->time_to_die);
		pthread_mutex_unlock(philo->left_fork);
		return (NULL);
	}
	//if (philo->id % 2 == 0)
	//	ft_usleep(1);
	while (!is_dead(philo))
	{
		eat(philo);
		philo_sleep(philo);
		think(philo);
	}
	return (NULL);
}

static void	create_and_join_threads(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->data->nbr_philo)
	{
		pthread_create(&philo[i].thread, NULL, routine, &philo[i]);
		i++;
	}
	monitor(philo);
	i = 0;
	while (i < philo->data->nbr_philo)
	{
		pthread_join(philo[i].thread, NULL);
		i++;
	}
	i = 0;
	while (i < philo->data->nbr_philo)
	{
		pthread_mutex_destroy(&philo->data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&philo->data->print);
	pthread_mutex_destroy(&philo->data->dead_lock);
	pthread_mutex_destroy(&philo->data->meal_lock);
}

int	main(int argc, char **argv)
{
	t_data		*data;
	t_philo		*philo;

	if (argc != 5 && argc != 6)
		return (printf("invalid number of arguments\n"), 1);
	if (check_args(argc, argv))
		return (printf("Arguments must be a positive numeric numbers\n"), 1);
	if (argv[1][0] == '0')
		return (printf("Must be at least 1 Philosopher\n"), 1);
	data = malloc(sizeof(t_data));
	if (!data)
		return (1);
	ft_bzero(data, sizeof(t_data));
	init_data(data, argc, argv);
	philo = malloc(sizeof(t_philo) * data->nbr_philo);
	if (!philo)
		return (free(data->forks), free(data), 1);
	init_philo(philo, data);
	create_and_join_threads(philo);
	free_all(philo);
	return (0);
}
