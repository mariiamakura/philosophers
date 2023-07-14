/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_act.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparasku <mparasku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 17:15:47 by mparasku          #+#    #+#             */
/*   Updated: 2023/07/14 16:50:48 by mparasku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	put_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

void	take_forks(t_philo *philo)
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
		if (philo->data->rules->philo_num == 1)
		{
			pthread_mutex_unlock(philo->r_fork);
			return ;
		}
		pthread_mutex_lock(philo->l_fork);
		message(TEAKEN_FORK, philo);
	}
}

void	message(char *str, t_philo *philo)
{
	long	time;

	pthread_mutex_lock(&philo->data->lock);
	time = ft_get_time() - philo->data->start_time;
	if (philo->data->is_dead == 0)
		printf("%lu %i %s\n", time, philo->id, str);
	if (ft_strcmp(DIED, str) == 0 && philo->data->is_dead == TRUE
		&& philo->eating == FALSE)
		printf("%lu %i %s\n", time, philo->id, str);
	pthread_mutex_unlock(&philo->data->lock);
}

void	eat(t_philo *philo)
{
	take_forks(philo);
	if (philo->data->rules->philo_num == 1)
		return ;
	philo->eating = TRUE;
	message(EATING, philo);
	philo->time_die = ft_get_time() + philo->data->rules->time_die;
	usleep(philo->data->rules->time_eat * 1000);
	philo->eating = FALSE;
	philo->meal_times++;
	put_forks(philo);
	message(SLEEPING, philo);
	usleep(philo->data->rules->time_sleep * 1000);
}
