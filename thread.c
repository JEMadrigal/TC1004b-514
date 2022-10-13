#include <stdio.h>
#include <pthread.h>

typedef struct threadData{
    int threadId;
    char name[20];
} ThreadData;
typedef char caracter;

void *holaMundo(void *arg){
    ThreadData *myData = (ThreadData *)arg;
    printf("Hola desde el hilo y mi id es %d\n", myData->threadId);
    pthread_exit(NULL);
}

int main(){
    ThreadData myData;
    for(int i = 0; i<100; i++){
    pthread_t threadId;
    myData.threadId = i;
    pthread_create(&threadId, NULL, holaMundo,(void *) &myData);
    }

    pthread_exit(NULL);
    printf("Nunca llega");
}