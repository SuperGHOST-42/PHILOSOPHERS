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
/*
Em t_data
nb_philos → número de filósofos
time_to_die → tempo máximo sem comer
time_to_eat → tempo de comer
time_to_sleep → tempo de dormir
must_eat_count → opcional
someone_died → flag para parar tudo
start_time → início da simulação
forks → array de mutexes, 1 por garfo
print → mutex para proteger printf
*/

typedef struct s_data
{
	int					nbr_philos;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	int					must_eat_count;
	int					someone_died;
	long				start_time;
	pthread_mutex_t		*forks;
	pthread_mutex_t 	print;
}	t_data;

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	long			last_meal;
	pthread_mutex_t *left_fork;
	pthread_mutex_t *right_fork;
	pthread_t		thread;
	t_data			*data;
}	t_philo;

long	ft_atol(const char *str);
void	init_data(t_data *data, int argc, char **argv);
void	init_mutexes(t_data *data);
void	init_philos(t_philo *philo, t_data *data);

//prints
void	print_data(t_data *data);
void	print_philos(t_philo *philos, int n);


#endif