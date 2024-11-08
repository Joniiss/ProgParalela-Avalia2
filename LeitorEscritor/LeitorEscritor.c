#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

pthread_rwlock_t trava;
int dado_compartilhado = 0;

void* leitor(void* arg) {
    pthread_rwlock_rdlock(&trava);
    printf("Leitor %ld: Leu dado_compartilhado = %d\n", (long)arg, dado_compartilhado);
    pthread_rwlock_unlock(&trava);
    return NULL;
}

void* escritor(void* arg) {
    pthread_rwlock_wrlock(&trava);
    dado_compartilhado += 1;
    printf("Escritor %ld: Atualizou dado_compartilhado para %d\n", (long)arg, dado_compartilhado);
    pthread_rwlock_unlock(&trava);
    return NULL;
}

int main() {
    pthread_t leitores[5], escritores[2];
    pthread_rwlock_init(&trava, NULL);

    for (long i = 0; i < 5; i++) {
        pthread_create(&leitores[i], NULL, leitor, (void*)i);
    }
    for (long i = 0; i < 2; i++) {
        pthread_create(&escritores[i], NULL, escritor, (void*)i);
    }

    for (int i = 0; i < 5; i++) {
        pthread_join(leitores[i], NULL);
    }
    for (int i = 0; i < 2; i++) {
        pthread_join(escritores[i], NULL);
    }

    pthread_rwlock_destroy(&trava);
    return 0;
}
