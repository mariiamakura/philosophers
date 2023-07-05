/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparasku <mparasku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 14:23:06 by mparasku          #+#    #+#             */
/*   Updated: 2023/07/05 16:54:28 by mparasku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

t_data	*alloc_structs(t_data *data)
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
	return (data);
}

t_data	*init_rules(char **av, int ac, t_data *data)
{
	t_rules	*rules;

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
	data->start_time = 0;
	return (data);
}

t_data	*init_forks(t_data *data)
{
	int	i;

	i = 0;
	if (pthread_mutex_init(&data->lock, NULL))
		return (NULL);
	while (i < data->rules->philo_num)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (NULL);
		i++;
	}
	i = 0;
	data->philos[0].r_fork = &data->forks[0];
	data->philos[0].l_fork = &data->forks[data->rules->philo_num - 1];
	i = 1;
	while (i < data->rules->philo_num)
	{
		data->philos[i].r_fork = &data->forks[i];
		data->philos[i].l_fork = &data->forks[i - 1];
		i++;
	}
	return (data);
}

t_data	*init_philo(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->rules->philo_num)
	{
		data->philos[i].data = data;
		data->philos[i].id = i + 1;
		data->philos[i].time_die = data->rules->time_die;
		data->philos[i].meal_times = 0;
		data->philos[i].eating = FALSE;
		data->philos[i].status = 0;
		if (pthread_mutex_init(&data->philos[i].lock, NULL) != 0)
			return (NULL);
		i++;
	}
	return (data);
}

t_data	*init(t_data *data, char **av, int ac)
{
	data = init_rules(av, ac, data);
	if (data == NULL)
		return (NULL);
	data = alloc_structs(data);
	if (data == NULL)
		return (ft_error_exit("Error alloc structs", data, 1));
	data = init_forks(data);
	data = init_philo(data);
	if (data == NULL)
		return (ft_error_exit("Error alloc mutex", data, 2));
	return (data);
}
