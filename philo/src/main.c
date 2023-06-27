/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparasku <mparasku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 16:20:50 by mparasku          #+#    #+#             */
/*   Updated: 2023/06/27 15:03:32 by mparasku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
#include "../include/init.h"

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

int main(int ac, char **av)
{
    t_data *data;
    t_rules *rules;

    if (!argm_parse(ac, av))
    {
        error_print();
        return (-1);
    }
    rules = init_rules(ac, av);
    if (rules == NULL)
    {
        error_print();
        return (-1);
    }
    print_rules(rules);
    data = init_data(av);
    if (data == NULL)
    {
        free_rules(rules);
        error_print();
        return (-1);
    }
    print_data(data);

    free_rules(rules); // write it!
    free_data(data); // write it!
    return(0);

}


//run like this > MallocNanoZone=0 ./a.out