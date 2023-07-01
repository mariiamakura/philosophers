
#include <stdio.h>
#include <stdlib.h>
#include "rules.h"
#include "util.h"

BOOL validate_rules_argument(const char *string, const char *name) {
    BIG_INT value = parse_number(string);

    if (!is_number(string)) {
        printf("Incorrect number: %s isn't number %s\n", name, string);
        return FALSE;
    }
    if (!is_int(value)) {
        printf("Incorrect number: %s isn't int %s\n", name, string);
        return FALSE;
    }
    if (value <= 0) {
        printf("Incorrect number: %s should be positive %s\n", name, string);
        return FALSE;
    }
    return TRUE;
}

t_rules *parse_rules(int ac, char **av) {
    if (ac < 5) {
        printf("Not enough arguments\n");
        return NULL;
    }

    if (!validate_rules_argument(av[2], "time_to_die")) {
        return NULL;
    }
    if (!validate_rules_argument(av[3], "time_to_eat")) {
        return NULL;
    }
    if (!validate_rules_argument(av[4], "time_to_sleep")) {
        return NULL;
    }
    if (ac >= 6 && !validate_rules_argument(av[5], "req_eat")) {
        return NULL;
    }
    if (ac >= 7 && !validate_rules_argument(av[6], "time_to_execute")) {
        return NULL;
    }
    int time_to_die = (int) parse_number(av[2]);
    int time_to_eat = (int) parse_number(av[3]);
    int time_to_sleep = (int) parse_number(av[4]);
    int req_eat = ac < 6 ? 0 : (int) parse_number(av[5]);
    int time_to_execute = ac < 7 ? 0 : (int) parse_number(av[6]);
    return create_rules(time_to_die, time_to_eat, time_to_sleep, req_eat, time_to_execute);
}

t_rules *create_rules(int time_to_die, int time_to_eat, int time_to_sleep, int req_eat, int time_to_execute) {
    t_rules *rules = (t_rules *) malloc(sizeof(t_rules));
    if (rules == NULL) {
        printf("Not enough memory: rules\n");
        return NULL;
    }
    rules->time_to_die = time_to_die;
    rules->time_to_eat = time_to_eat;
    rules->time_to_sleep = time_to_sleep;
    rules->req_eat = req_eat;
    rules->time_to_execute = time_to_execute;
    return rules;
}

void free_rules(t_rules *rules) {
    free(rules);
}