/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparasku <mparasku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 16:20:50 by mparasku          #+#    #+#             */
/*   Updated: 2023/06/22 17:27:39 by mparasku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"


void print_struct(t_queue *queue)
{
    printf("%i\n", queue->philo_total_num);
    printf("%lld\n", queue->time_to_died);
    printf("%lld\n", queue->time_to_eat);
    printf("%lld\n", queue->time_to_sleep);
    printf("%i\n", queue->each_philo_eat);
}

int	main(int ac, char **av)
{
    t_queue queue;

	if (ac == 5 || ac == 6) 
	{
		if (!(argm_parse(ac, av)) || !init_data(ac, av, &queue))
		{
			error_print();
			return (-1);
		}
        print_struct(&queue);
    }
	else
	{
		error_print();
        return (-1);
	}


    destroy(&queue);
}


//run like this > MallocNanoZone=0 ./a.out