/*Escribir un programa ISO C que procese el archivo de enteros de 2 bytes
bigendian cuyo nombre es recibido como parametro. El procesamiento consiste
en eliminar los numeros multiplos de 3, trabajando sobre el mismo archivo
(sin archivos intermedios ni en memoria)*/

#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/types.h>

void deleteNumber(FILE* file) {
    uint16_t numberRead = 0;

    fread(&numberRead, sizeof(uint16_t), 1, file);

    if (feof(file)) {
        fseek(file, -sizeof(uint16_t), SEEK_CUR);
        return;
    }

    while (!feof(file)) {
        fseek(file, -sizeof(uint16_t)*2, SEEK_CUR);
        fwrite(&numberRead, sizeof(uint16_t), 1, file);
        fread(&numberRead, sizeof(uint16_t), 1, file); //este es el numero que acabo de copiar, no me importa porque lo voy a pisar ya
        fread(&numberRead, sizeof(uint16_t), 1, file); //este fread me va a activar el EOF asi que aca no lo moveria, lo muevo afuera del while
    }

    fseek(file, -sizeof(uint16_t)*2, SEEK_CUR);
    fwrite(&numberRead, sizeof(uint16_t), 1, file);
}

int main(int argc, char** argv) {

    FILE* file = fopen(argv[1], "rb+");
    if (!file) return 1;

    uint16_t numberRead = 0;
    int position = 0;
    fread(&numberRead, sizeof(uint16_t), 1, file);

    while (!feof(file)) {
        if (numberRead % 3 == 0) {
            position = ftell(file); //backup de donde estaba antes de borrar el numero
            deleteNumber(file);
            ftruncate(fileno(file), ftell(file)); //borro lo que sobra (son 2 bytes que sobran)
            fseek(file, position - sizeof(uint16_t), SEEK_SET); //me muevo un numero para atras porque tengo que leer el que acabo de mover hacia la izquierda
        }
        fread(&numberRead, sizeof(uint16_t), 1, file);
    }

    fclose(file);

    return 0;
}
