
#include "bool.h"
#include "rules.h"
#include "forks.h"

typedef struct s_global_philosopher_args {
    pthread_mutex_t mutex;
    BOOL is_stopped;
    t_rules *rules;
} t_global_philosopher_args;

typedef struct s_local_philosopher_args {
    int index; // for debug purposes
    t_fork *lower; // left for every one, except last philosopher
    t_fork *higher; // right for every one, except last philosopher
} t_local_philosopher_args;

typedef struct s_philosopher_args {
    t_global_philosopher_args *global;
    t_local_philosopher_args *local;
} t_philosopher_args;

typedef struct s_philosopher_all_args {
    t_global_philosopher_args *global_args;
    t_local_philosopher_args *local_args_array;
    t_philosopher_args *args_array;
} t_philosopher_all_args;

BOOL is_stopped(t_global_philosopher_args *global_args);

void set_stopped(t_global_philosopher_args *global_args, BOOL is_stopped);

t_philosopher_all_args *create_philosopher_args(t_rules *rules, t_forks *forks);

void free_philosopher_args(t_philosopher_all_args *all_args);
