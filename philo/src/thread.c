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

BOOL thread_creating(t_threads *thread_data)
{
	pthread_t *threads;
	int i;

	pthread_mutex_init(&thread_data->mutex, NULL);

	threads = (pthread_t *)malloc(sizeof(pthread_t) * (thread_data->data->philo_num + 1));
	if (threads == NULL)
	{
		pthread_mutex_destroy(&thread_data->mutex);
		return FALSE;
	}
	thread_data->thread_stop = FALSE;

	i = 1;
	while (i <= thread_data->data->philo_num)
	{
		pthread_mutex_lock(&thread_data->mutex);
		thread_data->index = i;
		pthread_mutex_unlock(&thread_data->mutex);
		if (pthread_create(&threads[i], NULL, routine, (void *)thread_data) != 0)
		{
			thread_data->thread_stop = TRUE; // Set the stop flag to terminate other threads
			while (--i > 0)
				pthread_join(threads[i], NULL);
			free(threads);
			pthread_mutex_destroy(&thread_data->mutex);
			return FALSE;
		}
		i++;
	}

	i = 1;
	while (i <= thread_data->data->philo_num)
	{
		if (pthread_join(threads[i], NULL) != 0)
			return FALSE;
		i++;
	}

	free(threads);
	pthread_mutex_destroy(&thread_data->mutex);
	return TRUE;
}
