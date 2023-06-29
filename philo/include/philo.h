#ifndef PHILO_H
# define PHILO_H
# define BOOL int
# define TRUE 1
# define FALSE 0

# include <string.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdlib.h>
# include <limits.h>

typedef struct s_node
{
    int data;
    struct s_node *next;
} t_node;

typedef struct s_philo
{
    int index; //starts from 0
    BOOL in_queue; //whether philo is in queue
    int last_eat;
    int lunch_num; //how many times philo ate
} t_philo;

//data for queue
typedef struct s_data
{
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

typedef struct s_threads
{
	pthread_mutex_t mutex;
	t_data *data;
	t_rules *rules;
	int index;
	BOOL thread_stop;
} t_threads;

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

//free.c
void free_rules(t_rules *rules);
void *free_data(t_data *data);
void free_linked_list(t_node *node);

//init.c
t_philo *init_philo(int philo_num);
t_data *init_data(char **av);
t_rules *init_rules(int ac, char **av);
t_threads *init_threads_data(t_data *data, t_rules *rules);

//threads.c
BOOL thread_creating(t_threads *threads_data);
void *routine(void *data_ptr);

#endif