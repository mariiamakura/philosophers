
#include <stdio.h>
#include "philosopher.h"

void print_rules(t_rules *rules) {
    printf("time to die: %ld\n", rules->time_to_die);
    printf("time_to_eat: %i\n", rules->time_to_eat);
    printf("time_to_sleep: %i\n", rules->time_to_sleep);
    printf("req_eat: %i\n", rules->req_eat);
    printf("time_to_execute: %i\n", rules->time_to_execute);
}

void print_forks(t_forks *forks) {
    printf("Fork number: %i\n", forks->size);
    int i = 0;
    while (i < forks->size) {
        t_fork *fork = &forks->array[i];
        printf("Fork index: %i [%i]\n", fork->index, i);
        i++;
    }
}

int main(int ac, char **av) {
    t_rules *rules = parse_rules(ac, av);
    if (rules == NULL) {
        return -1;
    }
    t_forks *forks = parse_forks(ac, av);
    if (forks == NULL) {
        free_rules(rules);
        return -1;
    }

//    print_rules(rules);
//    print_forks(forks);

    execute_philosophers(rules, forks);

    free_rules(rules);
    free_forks(forks);
    return 0;
}