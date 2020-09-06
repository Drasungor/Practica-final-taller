/*
9)
Escriba un programa C que reciba por argumento el nombre de un archivo

de numeros binarios de 16 bits y lo procese sobre si mismo.

El procesamiento consiste en repetir los numeros que sean "multiplos de 5 + 1" (6, 11, 16...)

(El archivo se agranda)*/

#include <stdint.h>
#include <stdio.h>

int main(int argc, char** argv) {
    FILE* file = fopen(argv[1], "rb+");

    if (!file) return 0;

    int numbersToRepeat = 0;
    uint16_t numberRead = 0;
    int numberAmount = 0;

    fread(&numberRead, sizeof(uint16_t), 1, file);

    while (!feof(file)) { //Contamos la cantidad de numeros a duplicar
        ++numberAmount;
        if ((numberRead - 1) % 5 == 0) {
            ++numbersToRepeat;
        }
        fread(&numberRead, sizeof(uint16_t), 1, file);
    }

    int padding = 0;
    fseek(file, 0, SEEK_END);
    fwrite(&padding, sizeof(uint16_t), numbersToRepeat, file);

    fseek(file, -(numbersToRepeat+1)*sizeof(uint16_t), SEEK_END);
    fflush(file); //escribimos los cambios a disco

    FILE* aux = fopen(argv[1], "rb+"); //este lo usamos para escribir, el file original lo usamos para leer
    fseek(aux, -sizeof(uint16_t), SEEK_END);

    for (int i = 0; i < numberAmount; ++i) {
        fread(&numberRead, sizeof(uint16_t), 1, file);
        fwrite(&numberRead, sizeof(uint16_t), 1, aux);
        //printf("%u\n", numberRead);
        fseek(aux, -2*sizeof(uint16_t), SEEK_CUR);
        fseek(file, -2*sizeof(uint16_t), SEEK_CUR);
    }

    //HASTA ACA ANDA BIEN

    fflush(aux); //escribimos los cambios a disco

    fclose(file);
    file = fopen(argv[1], "rb+");

    fseek(file, sizeof(uint16_t)*numbersToRepeat, SEEK_SET);
    fseek(aux, 0, SEEK_SET);


    fread(&numberRead, sizeof(uint16_t), 1, file);

    while (!feof(file)) {
        //printf("%u\n", numberRead);
        if ((numberRead - 1) % 5 == 0) {
            fwrite(&numberRead, sizeof(uint16_t), 1, aux);
        }
        fwrite(&numberRead, sizeof(uint16_t), 1, aux);
        fread(&numberRead, sizeof(uint16_t), 1, file);
    }





    /*DEBUG*/
    fflush(aux); //escribimos los cambios a disco
    fseek(aux, -sizeof(uint16_t), SEEK_END);

    for (int i = 0; i < (numberAmount + numbersToRepeat); ++i) { //debug
        fread(&numberRead, sizeof(uint16_t), 1, aux);
        printf("%u\n", numberRead);
        fseek(aux, -2*sizeof(uint16_t), SEEK_CUR);
    }

    fclose(aux);
    fclose(file);

    return 0;
}
