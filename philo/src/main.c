/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparasku <mparasku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 16:20:50 by mparasku          #+#    #+#             */
/*   Updated: 2023/07/03 17:50:25 by mparasku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/* void free_data(t_data *data)
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

void ft_exit(t_data *data)
{

	pthread_mutex_destroy(&data->lock);
	free_data(data);

	// maybe flag 1 before lock are alloced
	// flag 2 when locks are alloced
	int	i;

	i = 0;

	while (i < data->rules->philo_num)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&data->philos[i].lock);
		i++;
	}
}

int ft_error(char *str, t_data *data)
{
	printf("%s\n", str);
	if (data != NULL)
		ft_exit(data);
	return (-1);
} */


int	main(int ac, char **av)
{
	t_data *data;

	data = NULL;
	if (!argm_parse(ac, av))
		return (error_print());
	data = init(data, av, ac);
	if (data == NULL)
		return(-1);
	//print_rules(data);
	//print_philo(data);
	destroy_mutex(data);
	free_data(data);
	

	return (0);
}

//run like this on mac > MallocNanoZone=0 ./a.out
//flag  -fsanitize=thread