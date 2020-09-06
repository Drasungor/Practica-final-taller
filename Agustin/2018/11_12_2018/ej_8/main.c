#define _POSIX_C_SOURCE 200112L
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <unistd.h>

//Asumo que los numeros vienen en big endian en el archivo
void procesar_archivo(FILE* reading, FILE* writing) {
    uint16_t number;
    //uint16_t number_correct_endian;
    int numbers_counter = 0;
    fread(&number, sizeof(uint16_t), 1, reading);
    while (!feof(reading)) {
        if (ntohs(number) % 16 != 0) {
            fwrite(&number, sizeof(uint16_t), 1, writing);
            numbers_counter++;
        }
        fread(&number, sizeof(uint16_t), 1, reading);
    }
    ftruncate(fileno(writing), numbers_counter * sizeof(uint16_t));
}

int main() {
    FILE* writing = fopen("valuesword.dat", "r+");
    FILE* reading = fopen("valuesword.dat", "r");
    procesar_archivo(reading, writing);
    fclose(reading);
    fclose(writing);
    return 0;
}
