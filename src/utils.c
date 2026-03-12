/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arpereir <arpereir@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 02:45:14 by arpereir          #+#    #+#             */
/*   Updated: 2026/03/12 15:25:15 by arpereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

long	ft_atol(const char *str)
{
	int		i;
	long	sign;
	long	result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + str[i] - '0';
		i++;
	}
	return (sign * result);
}

void	print_data(t_data *data)
{
	printf("----- DATA -----\n");
	printf("nbr_philos      : %d\n", data->nbr_philo);
	printf("time_to_die     : %ld\n", data->time_to_die);
	printf("time_to_eat     : %ld\n", data->time_to_eat);
	printf("time_to_sleep   : %ld\n", data->time_to_sleep);
	printf("must_eat_count  : %d\n", data->must_eat_count);
	printf("someone_died    : %d\n", data->someone_died);
	printf("start_time      : %ld\n", data->start_time);
	printf("forks ptr       : %p\n", (void *)data->forks);
	printf("print mutex     : %p\n", (void *)&data->print);
	printf("----------------\n");
}

void	print_philo(t_philo *philos, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		printf("----- PHILO %d -----\n", i);
		printf("id             : %d\n", philos[i].id);
		printf("meals_eaten    : %d\n", philos[i].meals_eaten);
		printf("last_meal      : %ld\n", philos[i].last_meal);
		printf("left_fork ptr  : %p\n", (void *)philos[i].left_fork);
		printf("right_fork ptr : %p\n", (void *)philos[i].right_fork);
		printf("thread         : %p\n", (void *)&philos[i].thread);
		printf("data ptr       : %p\n", (void *)philos[i].data);
		printf("--------------------\n");
		i++;
	}
}
void	*routine2(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(philo->right_fork);

	printf("philo %i has started\n", philo->id);
	printf("left fork = %p\n", (void*)philo->left_fork);
	printf("right fork = %p\n\n", (void*)philo->right_fork);

	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	return (NULL);
}

void	free_all(t_philo *philo)
{
	free(philo->data->forks);
	free(philo->data);
	free(philo);
}

void	print_msg(t_philo *philo, char *msg)
{
	pthread_mutex_lock(&philo->data->print);
	printf("%i %i %s", 300, philo->id, msg);
	pthread_mutex_unlock(&philo->data->print);
}