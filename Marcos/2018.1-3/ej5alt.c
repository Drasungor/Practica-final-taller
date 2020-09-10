/*5-Alt) Escribir un programa ISO C que procese el archivo "nros1byte.dat" sobre si mismo,
duplicando los bytes multiplos de 6.*/

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int countNumbersToDuplicate(FILE** file) {
    fseek(*file, 0, SEEK_SET);
    char number = 0;
    fread(&number, sizeof(char), 1, *file);
    int numbersToDuplicate = 0;

    while (!feof(*file)) {
        if (number % 6 == 0) {
            ++numbersToDuplicate;
        }
        fread(&number, sizeof(char), 1, *file);
    }

    return numbersToDuplicate;
}

int movePaddingToBeg(FILE** file, int originalFileSize) {
    int writePosition = ftell(*file) - sizeof(char);
    int readPosition = originalFileSize - sizeof(char);
    char number = 0;
    fseek(*file, readPosition, SEEK_SET);
    fread(&number, sizeof(char), 1, *file);
    readPosition -= sizeof(char);
    int stopCondition = (int)(-2*sizeof(char));

    while (readPosition > stopCondition) {
        fseek(*file, writePosition, SEEK_SET);
        fwrite(&number, sizeof(char), 1, *file);
        writePosition -= sizeof(char);
        fseek(*file, readPosition, SEEK_SET);
        fread(&number, sizeof(char), 1, *file);
        readPosition -= sizeof(char);
    }

    return (writePosition + sizeof(char));
}

int main() {
    const char* fileName = "nros1byte.dat";
    FILE* file = fopen(fileName, "rb+");
    if (!file) {
        fprintf(stderr, "Could not open file, check if it exists\n");
        return 1;
    }
    fseek(file, 0, SEEK_END);
    int originalFileSize = ftell(file);
    int numbersToDuplicate = countNumbersToDuplicate(&file);
    fseek(file, 0, SEEK_END);
    char padding = 0;
    for (int i = 0; i < numbersToDuplicate; ++i) {
        fwrite(&padding, sizeof(char), 1, file);
    }

    int readPosition = movePaddingToBeg(&file, originalFileSize);
    int writePosition = 0;
    char number = 0;
    fseek(file, readPosition, SEEK_SET);
    fread(&number, sizeof(char), 1, file);
    readPosition += sizeof(char);

    while (!feof(file)) {
        fseek(file, writePosition, SEEK_SET);
        fwrite(&number, sizeof(char), 1, file);
        writePosition += sizeof(char);
        if (number % 6 == 0) {
            fwrite(&number, sizeof(char), 1, file);
            writePosition += sizeof(char);
        }
        fseek(file, readPosition, SEEK_SET);
        fread(&number, sizeof(char), 1, file);
        readPosition += sizeof(char);
    }

    fclose(file);
    return 0;
}