/*1) Escribir un programa C que reciba por argumento el nombre de un archivo
y lo procese sobre si mismo. El procesamiento consiste en eliminar toda secuencia
de caracteres consecutivos repetidos, dejando en su lugar solo un caracter de dicha
secuencia. EJ: "abcddeeefgggghee" debe ser reemplazada por "abcdefghe"*/

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char** argv) {
    if (argc < 2) return 1;
    const char* fileName = argv[1];
    FILE* file = fopen(fileName, "r+");

    int writePosition = 0;
    int readPosition = 0;

    char currentChar = 0;
    char nextChar = 0;
    fread(&currentChar, sizeof(char), 1, file);
    fread(&nextChar, sizeof(char), 1, file);
    readPosition += 2*sizeof(char);

    while (!feof(file)) {
        if (currentChar != nextChar) {
            fseek(file, writePosition, SEEK_SET);
            fwrite(&currentChar, sizeof(char), 1, file);
            writePosition += sizeof(char);
            currentChar = nextChar;
        }
        fseek(file, readPosition, SEEK_SET);
        fread(&nextChar, sizeof(char), 1, file);
        readPosition += sizeof(char);
    }

    fseek(file, writePosition, SEEK_SET);
    fwrite(&currentChar, sizeof(char), 1, file); //para el ultimo caracter
    writePosition += sizeof(char);
    ftruncate(fileno(file), writePosition);
    fclose(file);
    return 0;
}