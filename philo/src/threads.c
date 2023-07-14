/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparasku <mparasku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 16:57:01 by mparasku          #+#    #+#             */
/*   Updated: 2023/07/14 17:59:19 by mparasku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*p_routine(void *philo_ptr)
{
	t_philo	*philo;

	philo = (t_philo *) philo_ptr;
	philo->time_die = philo->data->rules->time_die + ft_get_time();
	pthread_create(&philo->t1, NULL, &supervisor, philo);
	while (philo->data->is_dead == FALSE)
	{
		eat(philo);
		if (philo->data->rules->philo_num == 1)
			return ((void *)0);
		message(THINKING, philo);
		usleep(1000);
	}
	return ((void *)0);
}

void	*supervisor(void *philo_ptr)
{
	t_philo	*philo;

	philo = (t_philo *)philo_ptr;
	while (philo->data->is_dead == FALSE)
	{
		pthread_mutex_lock(&philo->lock);
		if (ft_get_time() >= philo->time_die && philo->eating == 0)
		{
			philo->data->is_dead = TRUE;
			message(DIED, philo);
			//pthread_mutex_unlock(&philo->lock);
		}
		if (philo->meal_times == philo->data->rules->req_eat)
		{;
			philo->data->finished++;
			//philo->meal_count++;
			//pthread_mutex_unlock(&philo->lock);
		}
		pthread_mutex_unlock(&philo->lock);
		usleep(100);
	}
	return ((void *)0);
}

void *enough_eat(void *data_ptr)
{
	t_philo*philo;

	philo = (t_philo *)data_ptr;
	while (philo->data->is_dead == FALSE)
	{
		pthread_mutex_lock(&philo->data->d_lock);
		if (philo->data->finished >= philo->data->rules->philo_num)
		{
			philo->data->is_dead = TRUE;
			pthread_mutex_lock(&philo->data->d_lock);
			break ;
		}
		pthread_mutex_lock(&philo->data->d_lock);
	}
	return((void *)0);
}

int	thread_init(t_data *data)
{
	int			i;
	pthread_t	t0;

	i = 0;
	data->start_time = ft_get_time();
	if (data->start_time == -1)
		return (FALSE);
	if (data->rules->req_eat > 0)
	{
		if (pthread_create(&t0, NULL, &enough_eat, &data->philos[0]))
			return (FALSE);
		pthread_detach(t0);
	}
	while (i < data->rules->philo_num)
	{
		if (pthread_create(&data->tid[i], NULL, &p_routine, &data->philos[i]))
			return (FALSE);
		i++;
	}
	i = 0;
	while (i < data->rules->philo_num)
	{
		if (pthread_join(data->tid[i], NULL) != 0)
			return (FALSE);
		i++;
	}
	return (TRUE);
}
