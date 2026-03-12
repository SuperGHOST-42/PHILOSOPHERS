# include "../includes/philosophers.h"

void	*routine(void *arg)
{
	t_philo	*philos;

	philos = (t_philo*)arg;
	pthread_mutex_lock(philos->data->forks);
	printf("philo %i has started\n", philos->id);
	pthread_mutex_unlock(philos->data->forks);
	return (NULL);
}

int		main(int argc, char **argv)
{
	t_data		*data;
	t_philo		*philos;
	int 		i, j;

	if (argc != 5 && argc != 6)
		return (printf("invalid number of arguments\n"), 1);
	data = malloc(sizeof(t_data));
	if (!data)
		return (1);
	init_data(data, argc, argv);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nbr_philos);
	if (!data->forks)
		return (free(data), 1);
	init_mutexes(data);
	philos = malloc(sizeof(t_philo) * data->nbr_philos);
	if (!philos)
		return (free(data->forks), free(data), 1);
	init_philos(philos, data);

	i = 0;
	while (i < data->nbr_philos)
	{
		pthread_create(&philos[i].thread, NULL, routine, &philos[i]);
		i++;
	}
	j = 0;
	while (j < data->nbr_philos)
	{
		pthread_join(philos[j].thread, NULL);
		j++;
	}

	free(philos);
	free(data->forks);
	free(data);
	return (0);
}
