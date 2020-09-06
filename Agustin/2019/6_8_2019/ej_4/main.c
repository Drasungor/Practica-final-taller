#define _POSIX_C_SOURCE 200112L
#include <stdio.h>
#include <stdint.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    FILE* escritura = fopen("mult7(backup).bin", "r+");
    FILE* lectura = fopen("mult7(backup).bin", "r");
    if ((!lectura) || ((!lectura))) {
        printf("Archivo invalido\n");
        return  -1;
    }
    int cantidad_final_numeros = 0;
    uint16_t aux;
    fread(&aux, sizeof(uint16_t), 1, lectura);
    aux = ntohs(aux);
    while (!feof(lectura)) {
        if (aux % 7 != 0) {
            aux = htons(aux);
            fwrite(&aux, sizeof(uint16_t), 1, escritura);
            cantidad_final_numeros++;
        }
        fread(&aux, sizeof(uint16_t), 1, lectura);
        aux = ntohs(aux);
    }
    ftruncate(fileno(escritura), cantidad_final_numeros * sizeof(uint16_t));
    fclose(lectura);
    fclose(escritura);
    return 0;
}
