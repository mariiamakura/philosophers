/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparasku <mparasku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 16:20:50 by mparasku          #+#    #+#             */
/*   Updated: 2023/06/29 15:37:13 by mparasku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void print_rules(t_rules *rules)
{
    printf("time to die: %i\n", rules->time_to_died);
    printf("time_to_eat: %i\n", rules->time_to_eat);
    printf("time_to_sleep: %i\n", rules->time_to_sleep);
    printf("req_eat: %i\n", rules->req_eat);
}

void print_data(t_data *data)
{
    t_philo *philo;
    int i;

    i = 0;

    printf("philo_num: %i\n", data->philo_num);
    printf("is_stop: %i\n", data->is_stop);
    while (i < data->philo_num)
    {
        philo = &data->philos[i];
        printf("i: %i\n", i);
        printf("philo index: %i\n", philo->index);
        printf("philo in_queue: %i\n", philo->in_queue);
        printf("philo last_eat: %i\n", philo->last_eat);
        printf("philo lunch_num: %i\n", philo->lunch_num);
        i++;
    }
}

void print_queue(t_data *data)
{
	t_node *node = data->queue;

	printf("The queue: ");
	while (node != NULL)
	{
		printf("philo num %i\n", node->data);
		node = node->next;
	}
}


int main(int ac, char **av)
{
    t_data *data;
    t_rules *rules;
	t_threads *threads_data;

	data = NULL;
	rules = NULL;
	threads_data = NULL;
    if (!argm_parse(ac, av))
		error_print();
    rules = init_rules(ac, av);
    if (rules == NULL)
        error_print();;
    data = init_data(av);
    if (data == NULL)
    {
        free_rules(rules);
        error_print();
    }
	threads_data = init_threads_data(data, rules);
	if (threads_data == NULL)
	{
		free_rules(rules);
		free_data(data);
		error_print();
	}
    if (!thread_creating(threads_data))
    {
        free_rules(rules);
        free_data(data);
		pthread_mutex_destroy(&threads_data->mutex);
		free(threads_data);
        error_print();
    }

    // //
    free_rules(rules);
    free_data(data);
    return(0);
}


//run like this on mac > MallocNanoZone=0 ./a.out
//flag  -fsanitize=thread