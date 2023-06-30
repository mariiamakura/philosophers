#include "../include/philo.h"

BOOL create_supervisor(t_threads *threads_data, pthread_t *threads)
{
	if (pthread_create(&threads[threads_data->data->philo_num], NULL, supervisor_routine, (void *)threads_data) != 0)
		return (FALSE);
	return (TRUE);
}

void free_threads(t_threads *threads_data, pthread_t *threads, int i)
{
    threads_data->is_stop = TRUE; // Set the stop flag to terminate other threads
    while (--i >= 0)
        if (pthread_join(threads[i], NULL) != 0)
            error_print();
    free(threads);
}

pthread_t *create_philos(t_threads *threads_data, pthread_t *threads)
{
    int i;

    i = 0;
    while (i < threads_data->data->philo_num)
    {
        pthread_mutex_lock(&threads_data->mutex);
        threads_data->index = i;
        pthread_mutex_unlock(&threads_data->mutex);
        if (pthread_create(&threads[i], NULL, philo_routine, (void *)threads_data) != 0)
        {
            free_threads(threads_data, threads, i);
            return (NULL);
        }
        usleep(100);
        i++;
        //without it threads will get the wrong index since they access data struct fast //maybe the deleting from queue by spervisor and cheking it will solve
    }
    return (threads);
}

BOOL thread_creating(t_threads *threads_data)
{

	int i;

	i = 0;
	pthread_t *threads;	threads = (pthread_t *)malloc(sizeof(pthread_t) * (threads_data->data->philo_num + 1));
    if (threads == NULL)
	{
        return (FALSE);
	}
	if (!create_supervisor(threads_data, threads))
	{
		free(threads);
		return (FALSE);
	}
    threads = create_philos(threads_data, threads);
	while (i <= threads_data->data->philo_num)
	{
		if (pthread_join(threads[i], NULL) != 0)
			return (FALSE);
		i++;
	}
	free(threads);
	return (TRUE);
}
