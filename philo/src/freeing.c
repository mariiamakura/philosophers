/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparasku <mparasku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 17:18:36 by mparasku          #+#    #+#             */
/*   Updated: 2023/07/05 17:15:22 by mparasku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	free_data(t_data *data)
{
	if (data->tid != NULL)
		free(data->tid);
	if (data->forks != NULL)
		free(data->forks);
	if (data->philos != NULL)
		free(data->philos);
	if (data->rules != NULL)
		free(data->rules);
	free(data);
}

void	destroy_mutex(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&data->lock);
	while (i < data->rules->philo_num)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&data->philos[i].lock);
		i++;
	}
}

t_data	*ft_error_exit(char *str, t_data *data, int flag)
{
	printf("%s\n", str);
	if (flag == 1)
	{
		free_data(data);
		return (NULL);
	}
	else if (flag == 2)
	{
		destroy_mutex(data);
		free_data(data);
		return (NULL);
	}
	else
		return (NULL);
}
