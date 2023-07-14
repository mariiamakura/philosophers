/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sem_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparasku <mparasku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 16:02:01 by mparasku          #+#    #+#             */
/*   Updated: 2023/07/14 14:20:51 by mparasku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

t_data	*sem_create(t_data *data)
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
	data->forks = sem_open("forks", O_CREAT | O_EXCL, 
			0600, data->rules->philo_num);
	if (data->death == SEM_FAILED)
		return (NULL);
	return (data);
}

void	*supervisor_bonus(void *data_ptr)
{
	t_philo	*philo;

	philo = (t_philo *)data_ptr;
	while (TRUE)
	{
		sem_wait(philo->data->death);
		if (philo->time_die <= ft_get_time())
		{
			message(DIED, philo);
			sem_post(philo->data->stop);
			break ;
		}
		sem_post(philo->data->death);
		sem_wait(philo->data->death);
		if (philo->meal_times == philo->data->rules->req_eat)
		{
			sem_post(philo->data->stop);
			break ;
		}
		sem_post(philo->data->death);
	}
	return ((void *)0);
}

void	p_routine(t_philo *philo)
{
	pthread_t	dead;

	philo->time_die = philo->data->rules->time_die + ft_get_time();
	pthread_create(&dead, NULL, supervisor_bonus, philo);
	pthread_detach(dead);
	while (TRUE)
	{
		take_forks(philo);
		message(EATING, philo);
		philo->time_die = ft_get_time() + philo->data->rules->time_die;
		usleep(philo->data->rules->time_eat * 1000);
		philo->meal_times++;
		put_forks_bonus(philo);
		message(SLEEPING, philo);
		usleep(philo->data->rules->time_sleep * 1000);
		message(THINKING, philo);
	}
}

void	ft_process_create(t_data *data)
{
	int	i;

	i = 0;
	data->start_time = ft_get_time();
	while (i < data->rules->philo_num)
	{
		data->philos[i].pid = fork();
		if (data->philos[i].pid == 0)
		{
			p_routine(&data->philos[i]);
		}
		i++;
		usleep(1);
	}
}
