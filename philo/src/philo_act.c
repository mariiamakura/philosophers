#include "../include/philo.h"

void put_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	printf("Thread #%i droped forks\n", philo->id);
}

void take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0) 
	{
        pthread_mutex_lock(philo->l_fork);
        pthread_mutex_lock(philo->r_fork);
    } 
	else 
	{
        pthread_mutex_lock(philo->r_fork);
        pthread_mutex_lock(philo->l_fork);
    }
}

void message(char *str, t_philo *philo)
{
	long	time;

	time = ft_get_time() - philo->data->start_time;
	if (ft_strcmp(DEID, str) == 0 && philo->data->is_dead == 1)
		printf("%lu %i %s\n", time, philo->id, str);
	if (philo->data->is_dead == 0)
		printf("%lu %i %s\n", time, philo->id, str);
}

void eat(t_philo *philo)
{
	take_forks(philo);
	if (philo->time_die == ft_get_time())
		philo->data->is_dead == TRUE;
	//pthread_mutex_lock(&philo->lock);
	philo->eating = TRUE;
	philo->time_die = ft_get_time() + philo->data->rules->time_die;
	printf("thread #%i is eating\n", philo->id);
	philo->meal_times++;
	philo->data->is_dead = TRUE;
	//pthread_mutex_unlock(&philo->lock);
	put_forks(philo);
	usleep(100);
}