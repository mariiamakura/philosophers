
#include "rules.h"
#include "forks.h"
#include "philosopher_args.h"

void *philosopher_routine(void *args);

void execute_philosophers(t_rules *rules, t_forks *forks);

void join_threads(pthread_t *threads, int size);
