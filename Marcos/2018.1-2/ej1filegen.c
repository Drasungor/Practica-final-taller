#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <arpa/inet.h>

int main() {

    FILE* file = fopen("ej1.bin", "wb+");

    int32_t currNum = 1;
    currNum = htonl(currNum);
    fwrite(&currNum, sizeof(int32_t), 1, file);
    currNum = 2;
    currNum = htonl(currNum);
    fwrite(&currNum, sizeof(int32_t), 1, file);
    currNum = 3;
    currNum = htonl(currNum);
    fwrite(&currNum, sizeof(int32_t), 1, file);
    currNum = 4;
    currNum = htonl(currNum);
    fwrite(&currNum, sizeof(int32_t), 1, file);
    currNum = 0xffffffff;
    fwrite(&currNum, sizeof(int32_t), 1, file);

    currNum = 10;
    currNum = htonl(currNum);
    fwrite(&currNum, sizeof(int32_t), 1, file);
    currNum = 11;
    currNum = htonl(currNum);
    fwrite(&currNum, sizeof(int32_t), 1, file);
    currNum = 12;
    currNum = htonl(currNum);
    fwrite(&currNum, sizeof(int32_t), 1, file);
    currNum = 13;
    currNum = htonl(currNum);
    fwrite(&currNum, sizeof(int32_t), 1, file);
    currNum = 0xffffffff;
    fwrite(&currNum, sizeof(int32_t), 1, file);

    currNum = 1;
    currNum = htonl(currNum);
    fwrite(&currNum, sizeof(int32_t), 1, file);
    currNum = 2;
    currNum = htonl(currNum);
    fwrite(&currNum, sizeof(int32_t), 1, file);
    currNum = 0xffffffff;
    fwrite(&currNum, sizeof(int32_t), 1, file);

    fclose(file);
    return 0;
}