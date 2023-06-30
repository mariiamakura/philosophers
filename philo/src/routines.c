#include "../include/philo.h"

void *philo_routine(void *data_ptr)
{
    t_threads *threads_data;
    int index;

    threads_data = (t_threads *)data_ptr;

    pthread_mutex_lock(&threads_data->mutex);
    index = threads_data->index;
    printf("Hello, this is thread #%i\n", index);
    pthread_mutex_unlock(&threads_data->mutex);

    return (NULL);
}

void *supervisor_routine(void *data_ptr)
{
    t_threads *threads_data;

    threads_data = (t_threads *)data_ptr;
    pthread_mutex_lock(&threads_data->mutex);
    printf("Supervisor is here!\n");
    pthread_mutex_unlock(&threads_data->mutex);
    return (NULL);
}