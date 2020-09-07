/* Escribir un programa que procese un archivo binario de enteros sin signo sobre si mismo.
El procesamiento consiste en leer pares de enteros de 1 byte cada uno y reemplazarlos por 3
enteros (el archivo se agranda): su suma, su resta y el OR logico entre ambos. */


#include <stdio.h>
#include<stdint.h>

int main(int argc, char** argv) {
    FILE* file = fopen(argv[1], "rb+");
    if(!file) return -1;

    uint8_t currNum;

    fseek(file, 0, SEEK_END);
    int fileSize = ftell(file);
    int cantNum = fileSize;
    uint8_t filler = 0;

    //Escribo basura
    for (size_t i = 0; i < fileSize / 2; i++) {
        fwrite(&filler, sizeof(uint8_t), 1, file);
    }

    //Paso la basura al principio
    for (size_t i = 0; i < fileSize; i++) {
        fseek(file, fileSize - i*sizeof(uint8_t) - 1, SEEK_SET);
        fread(&currNum, sizeof(uint8_t), 1, file);
        printf("%d\n", currNum);
        fseek(file, -i*sizeof(uint8_t) - 1, SEEK_END);
        fwrite(&currNum, sizeof(uint8_t), 1, file);
    }

    //Voy al primer numero dsps de la basura
    int readPos = fileSize/2;
    int writePos = 0;

    uint8_t firstNum;
    uint8_t secondNum;

    uint8_t sum, sub, or;

    fseek(file, readPos, SEEK_SET);
    fread(&firstNum, sizeof(uint8_t), 1, file);

    while (!feof(file)) {
        fread(&secondNum, sizeof(uint8_t), 1, file);
        readPos += 2;
        sum = firstNum + secondNum;
        sub = firstNum - secondNum;
        or = (firstNum | secondNum);
        fseek(file, writePos, SEEK_SET);
        fwrite(&sum, sizeof(uint8_t), 1, file);
        fwrite(&sub, sizeof(uint8_t), 1, file);
        fwrite(&or, sizeof(uint8_t), 1, file);
        writePos += 3;
        fseek(file, readPos, SEEK_SET);
        fread(&firstNum, sizeof(uint8_t), 1, file);
    }

    fclose(file);
    return 0;

}
