#include "../include/philo.h"

void *philo_routine(void *data_ptr)
{
    t_threads *threads_data;
    int index;

    threads_data = (t_threads *)data_ptr;
	index = threads_data->index;
	while (TRUE) 
	{
		pthread_mutex_lock(&threads_data->mutex);
		if (threads_data->is_stop == TRUE)
       		break;
		if (threads_data->data->philos[index].in_queue == FALSE)
			printf("Hello, this is thread #%i and i'm not in the queue\n", index);
		pthread_mutex_unlock(&threads_data->mutex);
		usleep(100);
	}
    return (NULL);
}

void *supervisor_routine(void *data_ptr)
{
	t_threads *threads_data;
	int thread_to_delete;

	threads_data = (t_threads *)data_ptr;
	thread_to_delete = 0;
	while (TRUE)
	{
		pthread_mutex_lock(&threads_data->mutex);
		if (threads_data->is_stop == TRUE)
			break;
		thread_to_delete = threads_data->data->queue->data;
		threads_data->data->philos[thread_to_delete].in_queue = FALSE;
		printf("Supervisor is here!\n");
		pthread_mutex_unlock(&threads_data->mutex);
		usleep(100);
	}
	return (NULL);
}