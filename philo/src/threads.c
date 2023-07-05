/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparasku <mparasku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 16:57:01 by mparasku          #+#    #+#             */
/*   Updated: 2023/07/05 17:47:03 by mparasku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*p_routine(void *philo_ptr)
{
	t_philo	*philo;

	philo = (t_philo *) philo_ptr;
	philo->time_die = philo->data->rules->time_die + ft_get_time();
	while (philo->data->is_dead == FALSE)
	{
		eat(philo);
		message(THINKING, philo);
		if (philo->meal_times == philo->data->rules->req_eat)
			philo->data->finished++;
	}
	return ((void *)0);
}

void	*supervisor(void *data_ptr)
{
	t_data	*data;
	int		i;

	i = 0;
	data = (t_data *)data_ptr;
	while (data->is_dead == FALSE)
	{
		i = 0;
		while (i < data->rules->philo_num)
		{
			if (ft_get_time() >= data->philos[i].time_die)
			{
				data->is_dead = TRUE;
				message(DIED, &data->philos[i]);
				break ;
			}
			if (data->finished == data->rules->philo_num)
			{
				data->is_dead = TRUE;
				break ;
			}
		}
	}
	return ((void *)0);
}

BOOL	thread_init(t_data *data)
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
		usleep(1);
		i++;
	}
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
