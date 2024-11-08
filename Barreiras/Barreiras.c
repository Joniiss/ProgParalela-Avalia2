#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_THREADS 5

pthread_barrier_t barreira;

void* funcao_thread(void* arg) {
    printf("Thread %ld chegou na barreira\n", (long)arg);
    pthread_barrier_wait(&barreira);
    printf("Thread %ld passou da barreira\n", (long)arg);
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    pthread_barrier_init(&barreira, NULL, NUM_THREADS);

    for (long i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, funcao_thread, (void*)i);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_barrier_destroy(&barreira);
    return 0;
}
