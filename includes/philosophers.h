/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arpereir <arpereir@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 02:45:12 by arpereir          #+#    #+#             */
/*   Updated: 2026/03/13 08:56:40 by arpereir         ###   ########.fr       */
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

typedef struct s_data
{
	long				nbr_philo;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	long				must_eat_count;
	int					someone_died;
	long				start_time;
	pthread_mutex_t		dead_lock;
	pthread_mutex_t		meal_lock;
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
//utils
int		check_args(int argc, char **argv);
int		ft_strncmp(char const *s1, char const *s2, size_t n);
long	ft_atol(const char *str);
long	get_time_in_ms(void);
void	init_data(t_data *data, int argc, char **argv);
void	init_mutexes(t_data *data);
void	init_philo(t_philo *philo, t_data *data);
void	free_all(t_philo *philo);
void	ft_bzero(void *s, size_t n);

//prints
void	print_status(t_philo *philo, char *msg);

//actions
void	eat(t_philo *philo);
void	philo_sleep(t_philo *philo);
void	think(t_philo *philo);

//monitor
int		is_dead(t_philo *philo);
void	monitor(t_philo *philo);

#endif