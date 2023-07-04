#include "../include/philo.h"

void *philo_routine(void *philo_ptr)
{
    t_philo *philo;

    philo = (t_philo *) philo_ptr;
    //time_die
    //supervisor
    while (philo->data->is_dead == 0)
    {

    }

}

BOOL thread_init(t_data *data)
{
    int i;
    pthread_t thread; //for monitor

    i = 0;
    data->start_time = get_time();
    if (data->start_time == -1)
        return (FALSE);
//    if (data->rules->req_eat > 0)
//    {
//        //write monitor
//    }

    while (i < data->rules->philo_num)
    {
        if (pthread_create(&data->tid[i], NULL, philo_routine, &data->philos[i]))
            return (FALSE);
        //sleep();
        i++;
    }
    //join
    return (TRUE);
}