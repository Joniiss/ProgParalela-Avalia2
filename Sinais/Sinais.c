#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void tratador_sinal(int sinal) {
    printf("Sinal %d recebido pela thread\n", sinal);
}

void* funcao_thread(void* arg) {
    printf("Thread aguardando sinal\n");
    pause();
    printf("Thread recebeu sinal\n");
    return NULL;
}

int main() {
    pthread_t thread;
    signal(SIGUSR1, tratador_sinal);
    pthread_create(&thread, NULL, funcao_thread, NULL);

    sleep(1);
    printf("Enviando sinal para thread\n");
    pthread_kill(thread, SIGUSR1);

    pthread_join(thread, NULL);
    return 0;
}
