/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arpereir <arpereir@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 02:45:12 by arpereir          #+#    #+#             */
/*   Updated: 2026/03/12 02:59:33 by arpereir         ###   ########.fr       */
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
	pthread_t	g	thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_data			*data;
}	t_philo;

long	ft_atol(const char *str);
void	innit_data(t_data *data, int argc, char **argv);
void	innit_mutexes(t_data *data);
void	innit_philo(t_philo *philo, t_data *data);

//prints
void	print_data(t_data *data);
void	print_philo(t_philo *philos, int n);

#endif