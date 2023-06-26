#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdlib.h>

typedef struct s_philo
{
    int index; //starts from 1
    uint64_t last_eat;
    u_int64_t time_to_eat; //how long philo is eating
    u_int64_t time_to_sleep; //how long philo is sleeping
    int in_the_queue; //starts with 1 - everyone in the queue
    int lunch_num; //how many times philo ate

} t_philo;

typedef struct s_queue
{
    t_philo *philo;
    int dead_philo; //in the beginning 0 - everyone is alive
    int philo_total_num;
    u_int64_t time_to_died; //after eating how fast philo die
    u_int64_t each_philo_eat; //if specified - each philo eats that num of time - then program finished
    u_int64_t time_to_eat; //how long philo is eating
    u_int64_t time_to_sleep; //how long philo is sleeping
    pthread_mutex_t	queue_lock;
    pthread_mutex_t write_lock;
} t_queue;

//error_handle.c
void	error_print();
int		argm_parse(int ac, char **av);
int		is_digit(char *str);

//utils.c
long long	ft_atoi(const char *str);

//init_data.c
int init(int ac, char **av, t_queue *queue);
int init_data(int ac, char **av, t_queue *queue);
void destroy(t_queue *queue);


#endif