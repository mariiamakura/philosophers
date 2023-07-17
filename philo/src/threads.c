/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparasku <mparasku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 16:57:01 by mparasku          #+#    #+#             */
/*   Updated: 2023/07/17 16:35:25 by mparasku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	is_dead_not(t_data *data)
{
	pthread_mutex_lock(&data->lock);
	if (data->is_dead == TRUE)
	{
		pthread_mutex_unlock(&data->lock);
		return (TRUE);
	}
	pthread_mutex_unlock(&data->lock);
	return (FALSE);
}

void	routine_2(t_philo *philo)
{
	while (is_dead_not(philo->data) == FALSE)
	{
		eat(philo);
		pthread_mutex_lock(&philo->lock);
		if (philo->data->rules->philo_num == 1)
		{
			pthread_mutex_unlock(&philo->lock);
			return ;
		}
		pthread_mutex_unlock(&philo->lock);
		message(THINKING, philo);
		usleep(1000);
		pthread_mutex_lock(&philo->data->lock);
		if (philo->meal_times == philo->data->rules->req_eat)
		{
			philo->data->finished++;
		}
		pthread_mutex_unlock(&philo->data->lock);
	}
}

void	*p_routine(void *philo_ptr)
{
	t_philo	*philo;

	philo = (t_philo *) philo_ptr;
	pthread_mutex_lock(&philo->lock);
	philo->time_die = philo->data->rules->time_die + ft_get_time();
	pthread_mutex_unlock(&philo->lock);
	routine_2(philo);
	return ((void *)0);
}

void	*supervisor(void *data_ptr)
{
	t_data	*data;
	int		i;

	i = 0;
	data = (t_data *)data_ptr;
	while (TRUE)
	{
		i = 0;
		while (i < data->rules->philo_num)
		{
			if (check_death(data, i) == TRUE)
				break ;
			if (eaten_all(data, i) == TRUE)
				break ;
			i++;
		}
		pthread_mutex_lock(&data->philos[0].data->lock);
		if (data->philos[0].data->is_dead)
		{
			pthread_mutex_unlock(&data->philos[0].data->lock);
			break ;
		}
		pthread_mutex_unlock(&data->philos[0].data->lock);
	}
	return ((void *)0);
}

int	thread_init(t_data *data)
{
	int			i;
	pthread_t	supervisor_s;

	i = 0;
	data->start_time = ft_get_time();
	if (data->start_time == -1)
		return (FALSE);
	while (i < data->rules->philo_num)
	{
		if (pthread_create(&data->tid[i], NULL, p_routine, &data->philos[i]))
			return (FALSE);
		i++;
	}
	usleep(100);
	if (pthread_create(&supervisor_s, NULL, supervisor, data))
		return (FALSE);
	i = 0;
	while (i < data->rules->philo_num)
	{
		if (pthread_join(data->tid[i], NULL) != 0)
			return (FALSE);
		i++;
	}
	pthread_join(supervisor_s, NULL);
	return (TRUE);
}
