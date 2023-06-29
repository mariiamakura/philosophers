#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    pthread_mutex_t mutex;
    int *data;
    int size;
} ThreadData;

void *threadRoutine(void *arg) {
    ThreadData *threadData = (ThreadData *)arg;

    pthread_mutex_lock(&threadData->mutex);
    for (int i = 0; i < threadData->size; i++) {
        printf("Thread %lu: Data[%d] = %d\n", pthread_self(), i, threadData->data[i]);
    }
    pthread_mutex_unlock(&threadData->mutex);

    return NULL;
}

int main() {
    int data[] = {1, 2, 3, 4, 5};
    int size = sizeof(data) / sizeof(data[0]);

    pthread_mutex_t mutex;
    pthread_mutex_init(&mutex, NULL);

    ThreadData threadData;
    threadData.mutex = mutex;
    threadData.data = data;
    threadData.size = size;

    pthread_t thread1, thread2;

    pthread_create(&thread1, NULL, threadRoutine, (void *)&threadData);
    pthread_create(&thread2, NULL, threadRoutine, (void *)&threadData);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    pthread_mutex_destroy(&mutex);

    return 0;
}
