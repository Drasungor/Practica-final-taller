/*Escriba una rutina que procese un archivo binario indicado por parametro sobre
si mismo sumarizando los listados de numeros que posee almacenado. La sumarizacion
consiste en recorrer los valores enteros de 32 bits con signo grabados en formato
big-endian y acumular sus valores hasta encontrar el valor 0xffffffff que se
considera un separador entre listados.

Todos los valores enteros detectados son reemplazados por su sumatoria
(en el mismo formato) manteniendo luego el elemento separador. Considere archivos
bien formados.*/

/*Asumo que el ultimo paquete tambien tiene el separador*/

#include <stdio.h>
#include <stdint.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char** argv) {
    if (argc < 2) return 1;
    const char* fileName = argv[1];

    FILE* file = fopen(fileName, "rb+");
    if (!file) return 1;

    int readPosition = 0;
    int writePosition = 0;
    const int32_t DELIM_NUM = 0xffffffff;

    int32_t number = 0;
    fread(&number, sizeof(int32_t), 1, file);
    readPosition += sizeof(int32_t);
    int32_t sum = 0;

    while (!feof(file)) {
        number = ntohl(number); /*de big endian al endiannes de mi maquina*/
        if (number == DELIM_NUM) {
            fseek(file, writePosition, SEEK_SET);
            sum = htonl(sum);
            fwrite(&sum, sizeof(int32_t), 1, file);
            fwrite(&DELIM_NUM, sizeof(int32_t), 1, file);
            writePosition += 2*sizeof(int32_t);
            sum = 0;
        } else {
            sum += number;
        }
        fseek(file, readPosition, SEEK_SET);
        fread(&number, sizeof(int32_t), 1, file);
        readPosition += sizeof(int32_t);
    }

    ftruncate(fileno(file), writePosition);
    fclose(file);
    return 0;
}