/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparasku <mparasku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 16:20:50 by mparasku          #+#    #+#             */
/*   Updated: 2023/07/13 13:39:22 by mparasku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

int	main(int ac, char **av)
{
	t_data	*data;

	data = NULL;
	if (!argm_parse(ac, av))
		return (error_print());
	data = init(data, av, ac);
	if (data == NULL)
		return (-1);
	data = sem_create(data);
	if (data == NULL)
		return (-1);
	sem_wait(data->stop);
	ft_process_create(data);
	sem_wait(data->stop);
	ft_destroy_all(data);
	
	// process_init(data);
	// destroy_mutex(data);
	// free_data(data);
	return (0);
}
