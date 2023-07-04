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

void eat(t_philo *philo)
{
	take_forks(philo);
	pthread_mutex_lock(&philo->lock);
	philo->eating = TRUE;
	printf("thread #%i is eating\n", philo->id);
	philo->meal_times++;
	pthread_mutex_unlock(&philo->lock);
	put_forks(philo);
}