#include "../include/init.h"

t_rules *init_rules(int ac, char **av)
{
    t_rules *rules;

    rules = (t_rules *)malloc(sizeof(t_rules));
    if (rules == NULL)
        return (NULL);
    rules->time_to_died = (int) ft_atoi(av[2]);
    rules->time_to_eat = (int) ft_atoi(av[3]);
    rules->time_to_sleep = (int) ft_atoi(av[4]);
    if (ac == 6)
        rules->req_eat = (int) ft_atoi(av[5]);
    return (rules);
}

void free_rules(t_rules *rules)
{
    free(rules);
}

t_philo *init_philo(int philo_num)
{
    t_philo *philos;
    t_philo *philo;
    int i;

    philo = NULL;
    i = 0;

    philos = (t_philo *) malloc(philo_num * sizeof (t_philo));
    if (philos == NULL)
    {
        return (NULL);
    }
    while (i < philo_num)
    {
        philo = &philos[i];
        philo->in_queue = TRUE;
        philo->index = i;
        philo->last_eat = 0;
        philo->lunch_num = 0;
        i++;
    }
    return (philos);
}

t_node *init_queue(int philo_num)
{
    t_node *queue;
    t_node *node;
    t_node *prev_node;
    int i;

    queue = NULL;
    node = NULL;
    prev_node = NULL;
    i = 0;
    while (i < philo_num)
    {
        prev_node = node;
        node = (t_node *) malloc(sizeof (t_node));
        if (node == NULL)
        {
            free_linked_list(queue);
            return (NULL);
        }
        if (queue == NULL)
            queue = node;
        if (prev_node != NULL)
        {
            prev_node->next = node;
        }
        node->data = i;
        i++;
    }
    return (queue);
}

t_data *init_data(char **av)
{
    t_data *data;
    int philo_num;
    t_philo *philos;
    t_node *queue;

    philo_num = (int) ft_atoi(av[1]);
    data = (t_data *) malloc(sizeof(t_data));
    if (data == NULL)
    {
        return (NULL);
    }
    philos = init_philo(philo_num);
    if (philos == NULL)
    {
        free(data);
        return (NULL);
    }
    queue = init_queue(philo_num);
    if (queue == NULL)
    {
        free(data);
        free(philos);
        return (NULL);
    }

    data->is_stop = FALSE;
    data->philo_num = philo_num;
    data->philos = philos;
    data->queue = queue;

    return data;
}

void free_data(t_data *data)
{
    free_linked_list(data->queue);
    free(data->philos);
}