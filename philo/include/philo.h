#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdlib.h>
# include <limits.h>
# include "linked_list.h"
# include "constants.h"

typedef struct s_philo
{
    int index; //starts from 1
    BOOL in_queue; //whether philo is in queue
    int last_eat;
    int lunch_num; //how many times philo ate
} t_philo;

//data for queue
typedef struct s_data
{
    pthread_mutex_t mutex;

    BOOL is_stop; // true so far while no one died or ate enough

    int philo_num;
    t_philo *philos;

    t_node *queue;
} t_data;

typedef struct s_rules
{
    int time_to_died; //after eating how fast philo die
    int time_to_eat; //how long philo is eating
    int time_to_sleep; //how long philo is sleeping
    int req_eat; //if specified - each philo eats that num of time - then program finished
} t_rules;

//error_handle.c
void error_print();
BOOL argm_parse(int ac, char **av);
BOOL is_digit(char *str);
BOOL philo_num_check(char *av);
BOOL is_int(char *av);

//main functions
void waiter_main(t_data *data, t_rules *rules);
    //waiter inside fun
    void send_to_eat(t_data *data);
    void check_rules(t_rules *rules);

void philo_main(t_data *data, int philo_num);
    //philo inside fun
    void wait_for_eat(t_data *data, int philo_num);
    void eat(t_data *data, int philo_num);
    void return_to_queue(t_data *data, int philo_num);


//utils.c
long long	ft_atoi(const char *str);

#endif