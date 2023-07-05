#include "../include/philo.h"

void put_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	//printf("Thread #%i droped forks\n", philo->id);
}

void take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0) 
	{
        pthread_mutex_lock(philo->l_fork);
		message(TEAKEN_FORK, philo);
        pthread_mutex_lock(philo->r_fork);
		message(TEAKEN_FORK, philo);
    } 
	else 
	{
        pthread_mutex_lock(philo->r_fork);
		message(TEAKEN_FORK, philo);
        pthread_mutex_lock(philo->l_fork);
		message(TEAKEN_FORK, philo);
    }
}

void message(char *str, t_philo *philo)
{
	long	time;

	time = ft_get_time() - philo->data->start_time;
	if (ft_strcmp(DIED, str) == 0 && philo->data->is_dead == TRUE && philo->eating == FALSE)
		printf("%lu %i %s\n", time, philo->id, str);
	if (philo->data->is_dead == 0)
		printf("%lu %i %s\n", time, philo->id, str);
}

void eat(t_philo *philo)
{
	take_forks(philo);
	//pthread_mutex_lock(&philo->lock);
	philo->eating = TRUE; //do i need it?
	message(EATING, philo);
	philo->time_die = ft_get_time() + philo->data->rules->time_die;
	usleep(philo->data->rules->time_eat * 1000);
	philo->eating = FALSE;
	philo->meal_times++;
	//pthread_mutex_unlock(&philo->lock);
	put_forks(philo);
	message(SLEEPING, philo);
	usleep(philo->data->rules->time_sleep * 1000);
}