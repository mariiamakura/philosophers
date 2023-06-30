#include "../include/philo.h"

void *philo_routine(void *data_ptr)
{
    t_threads *threads_data;
    int index;
	//int i = 0;

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
		//i++;
		usleep(100);
	}
    return (NULL);
}

void *supervisor_routine(void *data_ptr)
{
	t_threads *threads_data;
	int thread_to_delete;
	//int i = 0;

	threads_data = (t_threads *)data_ptr;
	thread_to_delete = 0;
	while (TRUE)
	{
		pthread_mutex_lock(&threads_data->mutex);
		if (threads_data->is_stop == TRUE)
			break;
		thread_to_delete = can_remove_index(threads_data);
		if (thread_to_delete != -1)
		{
			revome_node(&threads_data->data->queue, thread_to_delete);
			threads_data->data->philos[thread_to_delete].in_queue = FALSE;
			printf("Thread to delete #%i i the queue %i\n", thread_to_delete, threads_data->data->philos[thread_to_delete].in_queue);
		}
		printf("Supervisor is here!\n");
		pthread_mutex_unlock(&threads_data->mutex);
		//i++;
		usleep(100);
	}
	return (NULL);
}

int can_remove_index(t_threads *threads_data)
{
	t_node *current;
	int thread_index;
	int right_n;
	int left_n;

	thread_index = -1;
	right_n = 0;
	left_n = 0;
	current = threads_data->data->queue;
	while (current != NULL)
	{
		thread_index = current->data;
		if (thread_index == 0)
		{
			right_n = thread_index + 1;
			left_n = threads_data->data->philo_num - 1;
		}
		else if (thread_index == threads_data->data->philo_num - 1)
		{
			right_n = 0;
			left_n = thread_index - 1;
		}
		else 
		{
			right_n = thread_index + 1;
			left_n = thread_index - 1;
		}
		if (threads_data->data->philos[right_n].in_queue == TRUE &&
		threads_data->data->philos[left_n].in_queue == TRUE)
		{
			//printf("thread #%i, his neib right in queue %i lenft %i\n", thread_index, 
			//threads_data->data->philos[right_n].in_queue, threads_data->data->philos[left_n].in_queue);
			return (thread_index);
		}
		current = current->next;
	}
	return (-1);
}