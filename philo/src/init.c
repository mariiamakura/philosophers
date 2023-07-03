/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparasku <mparasku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 14:23:06 by mparasku          #+#    #+#             */
/*   Updated: 2023/07/03 16:35:52 by mparasku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

t_data *alloc_structs(t_data *data)
{
	data->tid = malloc(sizeof(pthread_t) * data->rules->philo_num);
	if (data->tid == NULL)
		return (NULL);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->rules->philo_num);
	if (data->forks == NULL)
		return (NULL);
	data->philos = malloc(sizeof(t_philo) * data->rules->philo_num);
	if (data->philos == NULL)
		return (NULL);
	data->lock = malloc(sizeof(pthread_mutex_t));
	if (data->lock == NULL)
		return (NULL);
	return (data);
}

t_data *init_rules(char **av, int ac, t_data *data)
{
	t_rules *rules;
	
	data = (t_data *)malloc(sizeof(t_data));
	rules = (t_rules *)malloc(sizeof(t_rules));
	if (rules == NULL || data == NULL)
		return (NULL);
	rules->philo_num = (int) ft_atoi(av[1]);
	rules->time_die = (int) ft_atoi(av[2]);
	rules->time_eat = (int) ft_atoi(av[3]);
	rules->time_sleep = (int) ft_atoi(av[4]);
	if (ac == 6)
		rules->req_eat = (int) ft_atoi(av[5]);
	else
		rules->req_eat = -1;
	data->rules = rules;
	data->is_dead = 0;
	data->finished = 0;
	return (data);
}


t_data *init(t_data *data, char **av, int ac)
{
	data = init_rules(av, ac, data);
	if (data == NULL)
		return (NULL);
	data = alloc_structs(data);
	if (data == NULL)
		return (NULL);
	return(data);
}