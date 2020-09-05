#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/types.h>

#include <arpa/inet.h>


void eliminar(FILE** file) {
    uint16_t currNum;
    fread(&currNum, sizeof(uint16_t), 1, *file);
    while (!feof(*file)) {
        fseek(*file, -2*sizeof(uint16_t), SEEK_CUR);
        fwrite(&currNum, sizeof(uint16_t), 1, *file);
        fseek(*file, sizeof(uint16_t), SEEK_CUR);
        fread(&currNum, sizeof(uint16_t), 1, *file);
    }
}

int main(int argc, char** argv) {
    FILE* file = fopen(argv[1], "rb+");
    if(!file) return -1;

    uint16_t currNum;
    int readPos = 0;
    int elim = 0;
    fseek(file, 0, SEEK_END);
    int fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);
    fread(&currNum, sizeof(uint16_t), 1, file);
    readPos += sizeof(uint16_t);


    while (!feof(file)) {
        currNum = ntohs(currNum);
        if (currNum % 16 == 0) {
            ++elim;
            readPos = ftell(file);
            eliminar(&file);
        }
        fseek(file, readPos, SEEK_SET);
        fread(&currNum, sizeof(uint16_t), 1, file);
        readPos += sizeof(uint16_t);
    }
    ftruncate(fileno(file), fileSize - elim*sizeof(uint16_t));


    fclose(file);
}
