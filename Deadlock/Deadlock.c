#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

pthread_mutex_t trava1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t trava2 = PTHREAD_MUTEX_INITIALIZER;

void* thread1(void* arg) {
    pthread_mutex_lock(&trava1);
    printf("Thread 1 adquiriu trava1\n");
    sleep(1);
    pthread_mutex_lock(&trava2);
    printf("Thread 1 adquiriu trava2\n");

    pthread_mutex_unlock(&trava2);
    pthread_mutex_unlock(&trava1);
    return NULL;
}

void* thread2(void* arg) {
    pthread_mutex_lock(&trava2);
    printf("Thread 2 adquiriu trava2\n");
    sleep(1);
    pthread_mutex_lock(&trava1);
    printf("Thread 2 adquiriu trava1\n");

    pthread_mutex_unlock(&trava1);
    pthread_mutex_unlock(&trava2);
    return NULL;
}

int main() {
    pthread_t t1, t2;
    pthread_create(&t1, NULL, thread1, NULL);
    pthread_create(&t2, NULL, thread2, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    return 0;
}
