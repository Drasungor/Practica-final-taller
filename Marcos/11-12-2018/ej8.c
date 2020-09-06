/*8) Escribir un programa ISO C que procese el archivo "valuesword.dat" sobre
si mismo, eliminando los words (2 bytes) multiplos de 16*/

/*Asumo que viene en big endian*/

#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/types.h>
#include <arpa/inet.h>

int main() {

    char* fileName = "valuesword.dat";
    FILE* file = fopen(fileName, "rb+");
    if (!file) return 1;

    int writePosition = 0;
    int readPosition = 0;

    uint16_t number = 0;
    fread(&number, sizeof(uint16_t), 1, file);
    readPosition += sizeof(uint16_t);

    while (!feof(file)) {
        number = ntohs(number);
        if (number % 16 != 0) {
            fseek(file, writePosition, SEEK_SET);
            number = htons(number);
            fwrite(&number, sizeof(uint16_t), 1, file);
            writePosition += sizeof(uint16_t);
        }
        fread(&number, sizeof(uint16_t), 1, file);
        readPosition += sizeof(uint16_t);
    }

    ftruncate(fileno(file), writePosition);

    fclose(file);
    return 0;
}