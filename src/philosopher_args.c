
#include "philosopher_args.h"
#include <stdlib.h>
#include <stdio.h>

BOOL is_stopped(t_global_philosopher_args *global_args) {
    pthread_mutex_lock(&global_args->mutex);
    BOOL is_stopped = global_args->is_stopped;
    pthread_mutex_unlock(&global_args->mutex);
    return is_stopped;
}

void set_stopped(t_global_philosopher_args *global_args, BOOL is_stopped) {
    pthread_mutex_lock(&global_args->mutex);
    global_args->is_stopped = is_stopped;
    pthread_mutex_unlock(&global_args->mutex);
}

t_philosopher_all_args *create_philosopher_args(t_rules *rules, t_forks *forks) {
    t_philosopher_args *args_array = (t_philosopher_args *) malloc(
            forks->size * sizeof(t_philosopher_args)
    );
    if (args_array == NULL) {
        printf("Not enough memory: args_array\n");
        return NULL;
    }
    t_global_philosopher_args *global_args = (t_global_philosopher_args *) malloc(sizeof(t_global_philosopher_args));
    if (global_args == NULL) {
        printf("Not enough memory: global_args\n");
        free(args_array);
        return NULL;
    }
    t_local_philosopher_args *local_args_array = (t_local_philosopher_args *) malloc(
            forks->size * sizeof(t_local_philosopher_args)
    );
    if (local_args_array == NULL) {
        printf("Not enough memory: local_args_array\n");
        free(args_array);
        free(global_args);
        return NULL;
    }
    pthread_mutex_init(&global_args->mutex, NULL);
    global_args->is_stopped = FALSE;
    global_args->rules = rules;
    int i = 0;
    while (i < forks->size) {
        t_philosopher_args *args = &args_array[i];
        t_local_philosopher_args *local_args = &local_args_array[i];
        local_args->index = i;
        if (i == forks->size - 1) {
            local_args->lower = &forks->array[0];
            local_args->higher = &forks->array[i];
        } else {
            local_args->lower = &forks->array[i];
            local_args->higher = &forks->array[i + 1];
        }
        args->global = global_args;
        args->local = local_args;
        i++;
    }

    t_philosopher_all_args *all_args = (t_philosopher_all_args *) malloc(sizeof(t_philosopher_all_args));
    if (all_args == NULL) {
        printf("Not enough memory: all_args\n");
        free(global_args);
        free(local_args_array);
        free(args_array);
        return NULL;
    }
    all_args->global_args = global_args;
    all_args->local_args_array = local_args_array;
    all_args->args_array = args_array;
    return all_args;
}

void free_philosopher_args(t_philosopher_all_args *all_args) {
    free(all_args->global_args);
    free(all_args->local_args_array);
    free(all_args->args_array);
    free(all_args);
}