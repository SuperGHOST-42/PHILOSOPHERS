#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>
# include <limits.h> 

typedef struct s_rules
{
	int					nbr_philos;
	long				time_die;
	long				time_eat;
	long				time_sleep;
	int					must_eat;
	long				start_time;
	pthread_mutex_t		*forks;
	pthread_mutex_t 	print;
}	t_rules;

typedef struct s_philo
{
	int			id;
	int			ate;
	long		last_meal;
	pthread_t	thread;
	t_rules		rules;
}	t_philo;

//long	get_time(void);
int		ft_atol(const char *str);

#endif