#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#define NUM_THREADS 10

int saldo;
sem_t protectSaldo;

void *suma(void *arg){
    sem_wait(&protectSaldo);
    printf("El saldo inicial es %d", saldo);
    saldo = saldo + 100;
    printf("El saldo despues es %d\n", saldo);
    sem_post(&protectSaldo);
    pthread_exit(NULL);
}

int main(){
    saldo = 0;
    pthread_t threadsInfo[NUM_THREADS];
    sem_init(&protectSaldo,0,1);

    for(int i = 0; i<NUM_THREADS; i++){
    pthread_create(&threadsInfo[i], NULL, suma, NULL);
    }

    for(int i = 0; i<NUM_THREADS; i++){
    pthread_join(threadsInfo[i], NULL);
    }

    printf("EL final es %d\n", saldo);
    pthread_exit(NULL);
    printf("Nunca llega");
}
