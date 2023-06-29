#include "../include/philo.h"

void *routine(void *data_ptr)
{
	t_threads *threads_data;
	int index;

	threads_data = (t_threads *)data_ptr;

	pthread_mutex_lock(&threads_data->mutex);
	index = threads_data->index;
	printf("Hello, this is thread #%i\n", index);
	pthread_mutex_unlock(&threads_data->mutex);

	return NULL;
}

BOOL thread_creating(t_threads *threads_data)
{
	pthread_t *threads;
	int i;

	i = 0;
	threads = (pthread_t *)malloc(sizeof(pthread_t) * (threads_data->data->philo_num + 1));
	if (threads == NULL)
		return FALSE;
	threads_data->thread_stop = FALSE;

	while (i < threads_data->data->philo_num)
	{
		pthread_mutex_lock(&threads_data->mutex);
		threads_data->index = i;
		pthread_mutex_unlock(&threads_data->mutex);
		if (pthread_create(&threads[i], NULL, routine, (void *)threads_data) != 0)
		{
			threads_data->thread_stop = TRUE; // Set the stop flag to terminate other threads
			while (--i > 0)
				pthread_join(threads[i], NULL);
			free(threads);
			return FALSE;
		}
		i++;
	}

	i = 0;
	while (i < threads_data->data->philo_num)
	{
		if (pthread_join(threads[i], NULL) != 0)
			return FALSE;
		i++;
	}
	free(threads);
	return TRUE;
}
