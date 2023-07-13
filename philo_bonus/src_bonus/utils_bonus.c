/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparasku <mparasku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 17:05:14 by mparasku          #+#    #+#             */
/*   Updated: 2023/07/13 18:06:30 by mparasku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

void	ft_destroy_all(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->rules->philo_num)
	{
		kill(data->philos[i].pid, SIGKILL);
		i++;
	}
	sem_close(data->death);
	sem_close(data->message);
	sem_close(data->stop);
	sem_close(data->forks);
	sem_unlink("message");
	sem_unlink("death");
	sem_unlink("stop");
	sem_unlink("forks");
	free(data->philos);
	free(data->rules);
	free(data);
}

void	message(char *str, t_philo *philo)
{
	long	time;

	time = ft_get_time() - philo->data->start_time;
	sem_wait(philo->data->message);
	printf("%lu %i %s\n", time, philo->id, str);
	sem_post(philo->data->message);
}

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
