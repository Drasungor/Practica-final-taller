/*5) Escribir un programa ISO C que procese el archivo "nros1byte.dat" sobre si mismo,
eliminando los bytes multiplos de 6.*/

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    const char* fileName = "nros1byte.dat";
    FILE* file = fopen(fileName, "rb+");
    if (!file) {
        fprintf(stderr, "Could not open file, check if it exists\n");
        return 1;
    }

    int readPosition = 0;
    int writePosition = 0;

    char number = 0;
    fread(&number, sizeof(char), 1, file);
    readPosition += sizeof(char);

    while (!feof(file)) {
        if (number % 6 != 0) {
            fseek(file, writePosition, SEEK_SET);
            fwrite(&number, sizeof(char), 1, file);
            writePosition += sizeof(char);
        }
        fseek(file, readPosition, SEEK_SET);
        fread(&number, sizeof(char), 1, file);
        readPosition += sizeof(char);
    }

    ftruncate(fileno(file), writePosition);
    fclose(file);
    return 0;
}