#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
    int pid = fork(); //Clona el proceso en absoluto, a diferencia del id, el cual cuando es igual a 0 se trata del proceso hijo, mientras que si es diferente de 0 es un proceso padre.

    if(pid == 0){
        printf("Soy el proceso hijo\n");
        //execl("/workspace/TC1004b-514/hola.exe", "hola.exe", NULL);  //arg(ruta de donde esta el arg, como llamar a lo que se va a comvertir)
        execl("hola.exe", "hola.exe", NULL);
        sleep(5);
    }else{
        printf("Soy el proceso padre\n");
        wait(NULL);
    }

    return 0;
}