/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparasku <mparasku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 16:20:50 by mparasku          #+#    #+#             */
/*   Updated: 2023/07/05 16:32:38 by mparasku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	main(int ac, char **av)
{
	t_data *data;

	data = NULL;
	if (!argm_parse(ac, av))
		return (error_print());
	data = init(data, av, ac);
	if (data == NULL)
		return(-1);
    thread_init(data);
	destroy_mutex(data);
	free_data(data);
	return (0);
}
