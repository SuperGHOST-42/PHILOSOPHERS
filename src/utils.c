/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arpereir <arpereir@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 02:45:14 by arpereir          #+#    #+#             */
/*   Updated: 2026/04/09 19:50:04 by arpereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	free_all(t_philo *philo)
{
	free(philo->data->forks);
	free(philo->data);
	free(philo);
}

void	print_status(t_philo *philo, char *msg)
{
	long	time;

	pthread_mutex_lock(&philo->data->print);
	if (!is_dead(philo) || ft_strncmp(msg, "died", 4) == 0)
	{
		time = get_time_in_ms() - philo->data->start_time;
		printf("%ld %d %s\n", time, philo->id, msg);
	}
	pthread_mutex_unlock(&philo->data->print);
}

long	get_time_in_ms(void)
{
	long			time_in_ms;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	time_in_ms = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (time_in_ms);
}

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*ptr;

	ptr = (unsigned char *)s;
	while (n--)
		*ptr++ = 0;
}

void	ft_usleep(time_t ms)
{
	long	wake_up;

	wake_up = get_time_in_ms() + ms;
	while (get_time_in_ms() < wake_up)
		usleep(100);
}
