/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sem_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparasku <mparasku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 16:02:01 by mparasku          #+#    #+#             */
/*   Updated: 2023/07/12 16:31:25 by mparasku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

t_data *sem_create(t_data *data)
{
	sem_unlink("death");
	sem_unlink("message");
	sem_unlink("stop");
	sem_unlink("forks");
	data->death = sem_open("death", O_CREAT | O_EXCL, 0600, 1);
	if (data->death == SEM_FAILED)
		return (NULL);
	data->message = sem_open("message", O_CREAT | O_EXCL, 0600, 1);
	if (data->death == SEM_FAILED)
		return (NULL);
	data->stop = sem_open("stop", O_CREAT | O_EXCL, 0600, 1);
	if (data->death == SEM_FAILED)
		return (NULL);
	data->forks = sem_open("forks", O_CREAT | O_EXCL, 0600, data->rules->philo_num);
	if (data->death == SEM_FAILED)
		return (NULL);
	return (data);
}

void	p_routine(t_philo *philo)
{

	philo->time_die = philo->data->rules->time_die + ft_get_time();
	while (philo->data->is_dead == FALSE)
	{
		eat(philo);
		message(THINKING, philo);
		if (philo->data->rules->philo_num == 1)
			return ((void *)0);
		if (philo->meal_times == philo->data->rules->req_eat)
			philo->data->finished++;
	}
	return ((void *)0);
}


void ft_process_create(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->rules->philo_num)
	{
		data->philos[i].pid = fork();
		if (data->philos[i].pid == 0)
		{
			p_routine(&data->philos[i]);
		}
		i++;
	}
}