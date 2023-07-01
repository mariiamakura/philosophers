
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "forks.h"
#include "bool.h"
#include "util.h"

BOOL validate_forks_argument(const char *string, const char *name) {
    BIG_INT value = parse_number(string);

    if (!is_number(string)) {
        printf("Invalid number: %s isn't number %s\n", name, string);
        return FALSE;
    }
    if (!is_int(value)) {
        printf("Invalid number: %s isn't int %s\n", name, string);
        return FALSE;
    }
    if (value < 2 || value > 200) {
        printf("Invalid number: %s is out of bounds [2, 200] %s\n", name, string);
        return FALSE;
    }
    return TRUE;
}

t_forks *parse_forks(int ac, char **av) {
    if (ac < 2) {
        return NULL;
    }

    if (!validate_forks_argument(av[1], "num_forks")) {
        return NULL;
    }
    int num_forks = (int) parse_number(av[1]);
    return create_forks(num_forks);
}

t_forks *create_forks(int num_forks) {
    t_forks *forks = (t_forks *) malloc(sizeof(t_forks));
    if (forks == NULL) {
        printf("Not enough memory: forks\n");
        return NULL;
    }
    t_fork *forks_array = (t_fork *) malloc(num_forks * sizeof(t_fork));
    if (forks_array == NULL) {
        printf("Not enough memory: forks_array\n");
        free(forks);
        return NULL;
    }
    int i = 0;
    while (i < num_forks) {
        t_fork *fork = &forks_array[i];
        fork->index = i;
        pthread_mutex_init(&fork->mutex, NULL);
        i++;
    }

    forks->array = forks_array;
    forks->size = num_forks;
    return forks;
}

void free_forks(t_forks *forks) {
    int i = 0;
    while (i < forks->size) {
        t_fork *fork = &forks->array[i];
        pthread_mutex_destroy(&fork->mutex);
        i++;
    }
    free(forks->array);
    free(forks);
}
