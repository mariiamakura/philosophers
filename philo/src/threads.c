#include "../include/philo.h"


void *philo_routine(void *philo_ptr)
{
    t_philo *philo;
	int i = 0;

    philo = (t_philo *) philo_ptr;
	philo->time_die = philo->data->rules->time_die + ft_get_time();
	
	while (philo->data->is_dead == FALSE)
    {
		eat(philo);
		printf("threads is dead = %i\n", philo->data->is_dead);
		i++;
		// if (i == 100) //check the time;
		// 	philo->data->is_dead = TRUE;
    }
	return ((void *)0);
}

void *supervisor(void *data_ptr)
{
	t_data *data;
	int i;

	data = (t_data *)data_ptr;
	i = 0;
	while (i < 20)
		i++;
	data->is_dead = TRUE;
	printf("supervisor *is_dead value %i\n", data->is_dead);
	return((void *)0);
}

BOOL thread_init(t_data *data)
{
    int i;
    // pthread_t supervisor_s;

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
		//printf("Thread #%i was created\n", i);
        usleep(100);
        i++;
    }
	i = 0;
	while (i < data->rules->philo_num)
	{
		if (pthread_join(data->tid[i], NULL) != 0)
			return (FALSE);
		i++;
	}
	return (TRUE);
}