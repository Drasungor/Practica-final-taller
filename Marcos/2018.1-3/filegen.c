#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <arpa/inet.h>

int main() {

    FILE* file = fopen("nros1byte.dat", "wb+");

    char currNum = 126;
    fwrite(&currNum, sizeof(char), 1, file);
    currNum = 2;
    fwrite(&currNum, sizeof(char), 1, file);
    currNum = 3;
    fwrite(&currNum, sizeof(char), 1, file);
    currNum = 4;
    fwrite(&currNum, sizeof(char), 1, file);

    currNum = 10;
    fwrite(&currNum, sizeof(char), 1, file);
    currNum = 11;
    fwrite(&currNum, sizeof(char), 1, file);
    currNum = 12;
    fwrite(&currNum, sizeof(char), 1, file);
    currNum = 13;
    fwrite(&currNum, sizeof(char), 1, file);

    currNum = 1;
    fwrite(&currNum, sizeof(char), 1, file);
    currNum = 6;
    fwrite(&currNum, sizeof(char), 1, file);

    fclose(file);
    return 0;
}