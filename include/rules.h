#ifndef RULES_H
#define RULES_H

typedef struct s_rules {
    long time_to_die; //after eating how fast philosopher die
    int time_to_eat; //how long philosopher is eating
    int time_to_sleep; //how long philosopher is sleeping
    int req_eat; //if specified - each philosopher eats that num of time - then program finished
    int time_to_execute; //if specified - each philosopher eats that num of time - then program finished
} t_rules;

t_rules *parse_rules(int ac, char **av);

t_rules *create_rules(int time_to_die, int time_to_eat, int time_to_sleep, int req_eat, int time_to_execute);

void free_rules(t_rules *rules);

#endif