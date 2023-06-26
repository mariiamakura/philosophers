#include "../include/philo.h"
int init_data(int ac, char **av, t_queue *queue)
{
    queue->philo_total_num = (int) ft_atoi(av[1]);
    queue->time_to_died = (u_int64_t) ft_atoi(av[2]);
    queue->time_to_eat = (u_int64_t) ft_atoi(av[3]);
    queue->time_to_sleep = (u_int64_t) ft_atoi(av[4]);
    queue->each_philo_eat = -1; //we never gonna have this number, so it save to set up when we dont have av[5]
    if (ac == 6)
        queue->each_philo_eat = (int) ft_atoi(av[5]);
    if (queue->philo_total_num <= 0 || queue->philo_total_num > 200 || queue->time_to_died < 0 ||
        queue->time_to_eat < 0 || queue->time_to_sleep < 0)
    {
        return (0);
    }
    queue->dead_philo = 0;
    if (pthread_mutex_init(&queue->queue_lock, NULL) != 0 || pthread_mutex_init(&queue->write_lock, NULL) != 0)
        return (0);
    return (1);
}


int init(int ac, char **av, t_queue *queue)
{
    if (!init_data(ac, av, queue))
    {
        return (0);
    }
    return (1);
}

void destroy(t_queue *queue)
{
    pthread_mutex_destroy(&queue->write_lock);
    pthread_mutex_destroy(&queue->queue_lock);
}