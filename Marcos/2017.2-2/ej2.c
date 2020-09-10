/*2) Escribir un programa C que procese el archivo "numeros.txt" sobre si mismo
(sin crear archivos intermedios y sin subir el archivo a memoria). El procesamiento
consiste en leer grupos de 5 digitos y reemplazarlos por 4 caracteres hexadecimales
que representen el mismo numero leido pero en hexadecimal.*/

/*Asumo que no hay \n al final*/

#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

#define DEC_BUF_SIZE 6 //+1 por el \0
#define HEX_BUF_SIZE 5 //+1 por el \0

void convertToHexString(char decBuffer[DEC_BUF_SIZE], char hexBuffer[HEX_BUF_SIZE]) {
    uint16_t number = strtol(decBuffer, NULL, 10);
    snprintf(hexBuffer, HEX_BUF_SIZE, "%04X", number);
}

int main() {
    const char* fileName = "numeros.txt";
    FILE* file = fopen(fileName, "r+");
    if (!file) {
        return 1;
    }

    char decBuffer[DEC_BUF_SIZE];
    char hexBuffer[HEX_BUF_SIZE];
    memset(decBuffer, 0, DEC_BUF_SIZE);

    int readPosition = 0;
    int writePosition = 0;

    fread(decBuffer, sizeof(char), DEC_BUF_SIZE - 1, file);
    readPosition += sizeof(char)*(DEC_BUF_SIZE - 1);

    while (!feof(file)) {
        convertToHexString(decBuffer, hexBuffer);
        fseek(file, writePosition, SEEK_SET);
        fwrite(hexBuffer, sizeof(char), HEX_BUF_SIZE - 1, file);
        writePosition += sizeof(char)*(HEX_BUF_SIZE - 1);
        fseek(file, readPosition, SEEK_SET);
        fread(decBuffer, sizeof(char), DEC_BUF_SIZE - 1, file);
        readPosition += sizeof(char)*(DEC_BUF_SIZE - 1);
    }

    ftruncate(fileno(file), writePosition);
    fclose(file);
    return 0;
}