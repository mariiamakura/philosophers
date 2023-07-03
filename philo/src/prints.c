#include "../include/philo.h"

void print_rules(t_data *data)
{
	printf("philo num: %i\n", data->rules->philo_num);
    printf("time to die: %i\n", data->rules->time_die);
    printf("time_to_eat: %i\n", data->rules->time_eat);
    printf("time_to_sleep: %i\n", data->rules->time_sleep);
    printf("req_eat: %i\n", data->rules->req_eat);
}

void print_philo(t_data *data)
{
	printf("philo id: %i\n", data->philos[0].id);
	printf("philo times ate: %i\n", data->philos[0].meal_times); 
}

/* void print_data(t_data *data)
{
    t_philo *philo;
    int i;

    i = 0;

    printf("philo_num: %i\n", data->philo_num);
    //printf("is_stop: %i\n", data->is_stop);
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
} */

/* void print_queue(t_data *data)
{
	t_node *node = data->queue;

	printf("The queue: \n");
	while (node != NULL)
	{
		printf("philo num %i\n", node->data);
		node = node->next;
	}
} */
