/*3) Escribir un programa que procese un archivo binario de enteros sin signo sobre
 si mismo. El procesamiento consiste en leer pares de enteros de 1 byte cada uno
 y reemplazarlos por 3 enteros (el archivo se agranda): su suma, su resta y
 el OR logico entre ambos.*/

#include <stdio.h>
#include <string.h>

int movePaddingToBeg(FILE** file, int originalFileSize) {
    int readPostion = originalFileSize - sizeof(char);
    int writePosition = ftell(*file) - sizeof(char);
    char currByte = 0;
    fseek(*file, readPostion, SEEK_SET);
    fread(&currByte, sizeof(char), 1, *file);
    readPostion -= sizeof(char);

    while (readPostion > -2) {
        fseek(*file, writePosition, SEEK_SET);
        fwrite(&currByte, sizeof(char), 1, *file);
        writePosition -= sizeof(char);
        fseek(*file, readPostion, SEEK_SET);
        fread(&currByte, sizeof(char), 1, *file);
        readPostion -= sizeof(char);
    }

    return (writePosition + sizeof(char));
}

void writeOperationsResult(FILE** file, char firstNumber, char secondNumber) {
    char result = firstNumber + secondNumber;
    fwrite(&result, sizeof(char), 1, *file);
    result = firstNumber - secondNumber;
    fwrite(&result, sizeof(char), 1, *file);
    result = firstNumber | secondNumber;
    fwrite(&result, sizeof(char), 1, *file);
}

int main(int argc, char** argv) {
    if (argc < 2) return 1;
    const char* fileName = argv[1];
    FILE* file = fopen(fileName, "rb+");

    fseek(file, 0, SEEK_END);
    int fileSize = ftell(file);
    int pairAmount = fileSize / 2; /*cuento la cantidad de parejas que tengo*/
    int extraSize = pairAmount * 3 - fileSize; /*nuevo tamanio menos anterior tamanio para tener la diferencia a agregar al final del archivo*/
    char padding = 0;
    for (int i = 0; i < extraSize; ++i) {
        fwrite(&padding, sizeof(char), 1, file); /*escribo el padding*/
    }

    int readPosition = movePaddingToBeg(&file, fileSize); /*muevo el padding al princpio del archivo*/
    int writePosition = 0;
    char firstNumber = 0;
    char secondNumber = 0;

    fseek(file, readPosition, SEEK_SET);
    fread(&firstNumber, sizeof(char), 1, file);
    readPosition += sizeof(char);
    fread(&secondNumber, sizeof(char), 1, file);
    readPosition += sizeof(char);

    while (!feof(file)) {
        fseek(file, writePosition, SEEK_SET);
        writeOperationsResult(&file, firstNumber, secondNumber);
        writePosition += sizeof(char)*3;
        fseek(file, readPosition, SEEK_SET);
        fread(&firstNumber, sizeof(char), 1, file);
        readPosition += sizeof(char);
        fread(&secondNumber, sizeof(char), 1, file);
        readPosition += sizeof(char);
    }


    fclose(file);
    return 0;
}