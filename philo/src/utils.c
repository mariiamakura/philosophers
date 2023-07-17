/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparasku <mparasku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 17:05:14 by mparasku          #+#    #+#             */
/*   Updated: 2023/07/17 16:25:42 by mparasku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

long	ft_get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) != 0)
		return (-1);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' && (s1[i] == s2[i]))
		i++;
	return (s1[i] - s2[i]);
}

long long	ft_atoi(const char *str)
	{
	int			neg;
	long long	number;
	int			i;

	neg = 1;
	i = 0;
	number = 0;
	if (!str)
		return (0);
	while ((str[i] >= '\t' && str[i] <= '\r') || str[i] == ' ')
		i++;
	if (str[i] == '-')
		neg = -1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		number = (number * 10) + (str[i] - '0');
		i++;
	}
	return (number * neg);
}

int	check_death(t_data *data, int i)
{
	pthread_mutex_lock(&data->philos[i].lock);
	if (ft_get_time() >= data->philos[i].time_die)
	{
		if (is_dead_not(data) == FALSE)
		{
			pthread_mutex_lock(&data->lock);
			data->philos[i].data->is_dead = TRUE;
			pthread_mutex_unlock(&data->lock);
			message(DIED, &data->philos[i]);
			pthread_mutex_unlock(&data->philos[i].lock);
			return (TRUE);
		}
	}
	pthread_mutex_unlock(&data->philos[i].lock);
	return (FALSE);
}

int	eaten_all(t_data *data, int i)
{
	pthread_mutex_lock(&data->lock);
	if (data->philos[i].data->finished == data->rules->philo_num)
	{
		data->philos[i].data->is_dead = TRUE;
		pthread_mutex_unlock(&data->lock);
		return (TRUE);
	}
	pthread_mutex_unlock(&data->lock);
	return (FALSE);
}
