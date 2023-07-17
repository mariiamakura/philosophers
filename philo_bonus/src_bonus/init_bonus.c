/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparasku <mparasku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 14:23:06 by mparasku          #+#    #+#             */
/*   Updated: 2023/07/17 16:44:45 by mparasku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

t_data	*alloc_structs(t_data *data)
{
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
	data->death = NULL;
	data->stop = NULL;
	data->message = NULL;
	data->forks = NULL;
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
		data->philos[i].pid = -1;
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
	data = init_philo(data);
	if (data == NULL)
		return (ft_error_exit("Error alloc mutex", data, 2));
	return (data);
}
