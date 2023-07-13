/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparasku <mparasku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 16:52:00 by mparasku          #+#    #+#             */
/*   Updated: 2023/07/13 17:53:13 by mparasku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	error_print(void)
{
	write(2, "Error occured\n", 15);
	return (-1);
}

int	is_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] < '0' || str[i] > '9')
		{
			return (FALSE);
		}
		i++;
	}
	return (TRUE);
}

int	philo_num_check(char *av)
{
	int	philo_num;

	philo_num = (int) ft_atoi(av);
	if (philo_num < 1 || philo_num > 200)
		return (FALSE);
	return (TRUE);
}

int	is_int(char *av)
{
	long long	value;

	value = ft_atoi(av);
	if (value < 0 || value > INT_MAX)
		return (FALSE);
	return (TRUE);
}

int	argm_parse(int ac, char **av)
{
	int	i;

	i = 2;
	if (ac != 5 && ac != 6)
		return (FALSE);
	if (!philo_num_check(av[1]))
		return (FALSE);
	while (i < ac)
	{
		if (!(is_digit(av[i])))
			return (FALSE);
		if (!(is_int(av[i])))
			return (FALSE);
		i++;
	}
	return (TRUE);
}
