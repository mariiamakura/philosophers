#include "../include/philo.h"


void *philo_routine(void *philo_ptr)
{
    t_philo *philo;

    philo = (t_philo *) philo_ptr;
	philo->time_die = philo->data->rules->time_die + ft_get_time();
	
	while (philo->data->is_dead == FALSE)
    {
		eat(philo);
		message(THINKING, philo);
	}
	return ((void *)0);
}

void *supervisor(void *data_ptr)
{
	t_data *data;
	int i;

	data = (t_data *)data_ptr;
	i = 0;

	while (data->is_dead == FALSE)
	{
		i = 0;
		while (i < data->rules->philo_num)
		{
			if (ft_get_time() >= data->philos[i].time_die)
			{
				data->is_dead = TRUE;
				//printf("is dead %i\n", data->is_dead);
				message(DIED, &data->philos[i]);
				break;
			}
		}
	}
	return ((void *)0);
}

BOOL thread_init(t_data *data)
{
    int i;
    pthread_t supervisor_s;

    i = 0;
    data->start_time = ft_get_time();
    if (data->start_time == -1)
	{
        return (FALSE);
	}
    while (i < data->rules->philo_num)
    {
        if (pthread_create(&data->tid[i], NULL, philo_routine, &data->philos[i]))
            return (FALSE);
        usleep(10);
        i++;
    }
	if (pthread_create(&supervisor_s, NULL, supervisor, data))
        return (FALSE);

	i = 0;

	pthread_join(supervisor_s, NULL);
	while (i < data->rules->philo_num)
	{
		if (pthread_join(data->tid[i], NULL) != 0)
			return (FALSE);
		i++;
	}
	return (TRUE);
}