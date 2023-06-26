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

int	main(int ac, char **av)
{
    t_queue queue;

	if (ac == 5 || ac == 6) 
	{
		if (!(argm_parse(ac, av)) || !init(ac, av, &queue))
		{
			error_print();
			return (-1);
		}
	}
	else
	{
		error_print();
        return (-1);
	}
    destroy(&queue);
}

//run like this > MallocNanoZone=0 ./a.out