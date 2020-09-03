/*4) Escribir un programa ISO C que procese el archivo "nros_2bytes_bigendian.dat" sobre
si mismo, eliminando los numeros multiplos de 7*/

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <arpa/inet.h>

void deleteNumber(FILE** file) {
    int readPosition = ftell(*file);
    fseek(*file, -sizeof(uint16_t), SEEK_CUR);
    int writePosition = ftell(*file);
    int positionBackUp = writePosition;

    fseek(*file, readPosition, SEEK_SET);
    uint16_t number = 0;
    fread(&number, sizeof(uint16_t), 1, *file);

    while (!feof(*file)) {
        readPosition += sizeof(uint16_t);
        fseek(*file, writePosition, SEEK_SET);
        fwrite(&number, sizeof(uint16_t), 1, *file);
        writePosition += sizeof(uint16_t);
        fseek(*file, readPosition, SEEK_SET);
        fread(&number, sizeof(uint16_t), 1, *file);
    }

    ftruncate(fileno(*file), writePosition);
    fseek(*file, positionBackUp, SEEK_SET);
}

int main(int argc, char** argv) {

    FILE* file = fopen("nros_2bytes_bigendian.dat", "rb+");
    if (!file) return 1;

    uint16_t number = 0;
    fread(&number, sizeof(uint16_t), 1, file);

    while (!feof(file)) {
        number = ntohs(number);
        if (number % 7 == 0) {
            deleteNumber(&file);
        }
        fread(&number, sizeof(uint16_t), 1, file);
    }

    fclose(file);

    return 0;
}