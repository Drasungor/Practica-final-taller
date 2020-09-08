/*Escriba una rutina que procese un archivo binario indicado por parametro sobre
si mismo sumarizando los listados de numeros que posee almacenado. La sumarizacion
consiste en recorrer los valores enteros de 32 bits con signo grabados en formato
big-endian y acumular sus valores hasta encontrar el valor 0xffffffff que se considera
 un separador entre listados.

Todos los valores enteros detectados son reemplazados por su sumatoria (en el mismo formati)
manteniendo luego el elemento separador. Considere archivos bien formados.*/

#include<stdio.h>
#include<stdint.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<unistd.h>
void eliminarNum(FILE** file) {
    int32_t currNum;
    fread(&currNum, sizeof(int32_t), 1, *file);

    while (!feof(*file)) {
        fseek(*file, -2*sizeof(int32_t), SEEK_CUR);
        fwrite(&currNum, sizeof(int32_t), 1, *file);
        fseek(*file, sizeof(int32_t), SEEK_CUR);
        fread(&currNum, sizeof(int32_t), 1, *file);
    }
}

int main (int argc, char** argv) {
    FILE* file = fopen("test.bin", "wb+");
    if(!file) return -1;

    int32_t currNum = 24586;
    currNum = htonl(currNum);
    fwrite(&currNum, sizeof(int32_t), 1, file);
    currNum = 13458;
    currNum = htonl(currNum);
    fwrite(&currNum, sizeof(int32_t), 1, file);
    currNum = 0xffffffff;
    currNum = htonl(currNum);
    fwrite(&currNum, sizeof(int32_t), 1, file);
    currNum = 128;
    currNum = htonl(currNum);
    fwrite(&currNum, sizeof(int32_t), 1, file);
    currNum = 32;
    currNum = htonl(currNum);
    fwrite(&currNum, sizeof(int32_t), 1, file);
    currNum = 0xffffffff;
    currNum = htonl(currNum);
    fwrite(&currNum, sizeof(int32_t), 1, file);

    fseek(file, 0, SEEK_END);
    int fileSize = ftell(file);

    fclose(file);

////////////////////////////////////////////////////////////////////////

    file = fopen("test.bin", "rb+");

    int32_t sum = 0;
    int cantNums = 0;
    int readPos = 0;
    int elim = 0;
    fread(&currNum, sizeof(int32_t), 1, file);
    readPos += 4;

    while (!feof(file)) {
        if (currNum != 0xffffffff) {
            currNum = ntohl(currNum);
            sum += currNum;
            ++cantNums;
            ++elim;
            eliminarNum(&file);
            ftruncate(fileno(file), fileSize - elim * sizeof(int32_t));
        } else {
            printf("%d\n", sum);
            sum = 0;
            cantNums = 0;
        }
        fseek(file, readPos, SEEK_SET);
        fread(&currNum, sizeof(int32_t), 1, file);
        readPos += 4;
    }

    fclose(file);
}
