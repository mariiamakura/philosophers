#ifndef FORKS_H
#define FORKS_H

#include <pthread.h>

typedef struct s_fork {
    int index; // for debug purposes
    pthread_mutex_t mutex;
} t_fork;

typedef struct s_forks {
    t_fork *array;
    int size;
} t_forks;

t_forks *parse_forks(int ac, char **av);

t_forks *create_forks(int num_forks);

void free_forks(t_forks *forks);

#endif