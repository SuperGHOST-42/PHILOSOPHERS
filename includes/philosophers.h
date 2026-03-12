/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arpereir <arpereir@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 02:45:12 by arpereir          #+#    #+#             */
/*   Updated: 2026/03/12 15:16:55 by arpereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>
# include <limits.h> 
# include "libft/libft.h"

typedef struct s_data
{
	int					nbr_philo;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	int					must_eat_count;
	int					someone_died;
	long				start_time;
	pthread_mutex_t		*forks;
	pthread_mutex_t		print;
}	t_data;

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	long			last_meal;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_data			*data;
}	t_philo;

long	ft_atol(const char *str);
void	init_data(t_data *data, int argc, char **argv);
void	init_mutexes(t_data *data);
void	init_philo(t_philo *philo, t_data *data);
void	free_all(t_philo *philo);

//prints
void	print_data(t_data *data);
void	print_philo(t_philo *philos, int n);
void	print_msg(t_philo *philo, char *msg);

//things
void	eat(t_philo *philo);
void	philo_sleep(t_philo *philo);
void	think(t_philo *philo);

#endif