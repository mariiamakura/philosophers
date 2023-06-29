#include "../include/philo.h"

void *routine(void *data_ptr) //i should pass here rules, data and index of thread(i)
{
    t_data *data;
    data = (t_data *)data_ptr;
    printf("Hello this is thread print\n");
    printf("philo num %i\n", data->philo_num);
    return (NULL);
}

BOOL thread_creating(t_data *data)
{
    pthread_t *threads;
    int i;

    i = 0;
    threads = (pthread_t *)malloc(sizeof(pthread_t) * (data->philo_num + 1));
    if (threads == NULL)
        return (FALSE);

    //i = 0 - for examinator thread
    i = 1;
    while (i <= data->philo_num)
    {
        if ((pthread_create(&threads[i], 0, routine, data) != 0))
            return (FALSE);
        i++;
    }
    i = 1;
    while (i <= data->philo_num)
    {
        if ((pthread_join(threads[i], 0)) != 0)
            return (FALSE);
        i++;
    }
    return (TRUE);
}