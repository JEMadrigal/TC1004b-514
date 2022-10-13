#include <stdio.h>

int main(){
    FILE *lsOutput;
    FILE *tomayInput;
    char readBuffer[80];
    lsOutput = popen("ls *c","r");
    tomayInput = popen("wc -l","w");

    while(fgets(readBuffer, 80, lsOutput)){
        fputs(readBuffer, tomayInput);
    }
    pclose(lsOutput);
    pclose(tomayInput);
}