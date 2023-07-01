
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include "philosopher.h"

void *philosopher_routine(void *void_args) {
    t_philosopher_args *args = (t_philosopher_args *) void_args;
    t_local_philosopher_args *local = args->local;
    t_global_philosopher_args *global = args->global;
    t_rules *rules = global->rules;

    // wait for notify is expected here

    struct timeval last_time_tv;
    struct timeval current_time_tv;
    gettimeofday(&last_time_tv, NULL);

    int i = 0;
//    printf("%i Start\n", local->index);
    while (!is_stopped(global) && (rules->req_eat <= 0 || i < rules->req_eat)) {
//        printf("%i Wait for forks\n", local->index);
        pthread_mutex_lock(&local->lower->mutex);
        pthread_mutex_lock(&local->higher->mutex);
        gettimeofday(&current_time_tv, NULL);
        long last_time = 1000000 * last_time_tv.tv_sec + last_time_tv.tv_usec;
        long current_time = 1000000 * current_time_tv.tv_sec + current_time_tv.tv_usec;
        if (current_time - last_time > rules->time_to_die) {
            pthread_mutex_unlock(&local->higher->mutex);
            pthread_mutex_unlock(&local->lower->mutex);
            printf("%i Die iterations %i\n", local->index, i);
            set_stopped(global, TRUE);
            break;
        }
//        printf("%i Eat\n", local->index);
        usleep(rules->time_to_eat);
        gettimeofday(&last_time_tv, NULL);
        pthread_mutex_unlock(&local->higher->mutex);
        pthread_mutex_unlock(&local->lower->mutex);
//        printf("%i Sleep\n", local->index);
        usleep(rules->time_to_sleep);
        ++i;
    }
//    printf("%i Finish iterations %i\n", local->index, i);
    return NULL;
}

void execute_philosophers(t_rules *rules, t_forks *forks) {
    t_philosopher_all_args *all_args = create_philosopher_args(rules, forks);
    if (all_args == NULL) {
        return;
    }
    pthread_t *threads = (pthread_t *) malloc(forks->size * sizeof(pthread_t));
    if (threads == NULL) {
        printf("Not enough memory: threads\n");
        free(all_args);
        return;
    }

    int i = 0;
    while (i < forks->size) {
        t_philosopher_args *args = &all_args->args_array[i];
        if (pthread_create(&threads[i], NULL, philosopher_routine, (void *) args) != 0) {
            printf("Cannot create thread %i\n", i);
            join_threads(threads, i + 1);
            free(threads);
            free_philosopher_args(all_args);
            return;
        }
        i++;
    }

    printf("All philosophers scheduled eating\n");

    // notify all is expected here

    if (all_args->global_args->rules->time_to_execute > 0) {
        usleep(all_args->global_args->rules->time_to_execute);
        printf("Stop is being requested\n");
        set_stopped(all_args->global_args, TRUE);
        printf("Stop was requested\n");
    }

    join_threads(threads, forks->size);
    printf("All philosophers stopped eating\n");

    free(threads);
    free_philosopher_args(all_args);
}

void join_threads(pthread_t *threads, int size) {
    int i = 0;
    while (i < size) {
        if (pthread_join(threads[i], NULL) != 0) {
            printf("Cannot join thread %i\n", i);
        }
        i++;
    }
}
