/*7) Escribir un programa C que procese el archivo "numeros.txt" sobre si mismo
(sin crear archivos intermedios y sin subir el archivo a memoria). El procesamiento
consiste en leer nros hexadecimales de 4 simbolos y reemplazarlos por su valor
decimal (en texto)*/

/*asumo orden en big endian como toda persona no hija de puta*/

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <math.h>
#include <sys/types.h>
#include <unistd.h>

#define HEX_BUF_SIZE 4
#define DEC_BUF_SIZE 7 //la max cantidad de digitos es 5 ya que 2^16-1 = 65535, luego 1 mas para una , para poder leer esta verga y +1 para el \0 porque el snprintf
                        //me mete el \0 y sino le diera el espacio extra me estaria pisando la ,

int getMultiplier(char hexSymbol) {
    int multiplier = 0;

    if ('0' <= hexSymbol && hexSymbol <= '9') {
        multiplier = hexSymbol - '0';
    } else if ('A' <= hexSymbol && hexSymbol <= 'F') {
        multiplier = hexSymbol - 'A' + 10;
    }

    return multiplier;
}

uint16_t getDecimal(char hexNumber[HEX_BUF_SIZE]) {
    uint16_t decimal = 0;

    for (int i = 0; i < HEX_BUF_SIZE; ++i) {
        decimal += getMultiplier(hexNumber[i]) * pow(16, HEX_BUF_SIZE - 1 - i);
    }

    return decimal;
}

void hexToDec(char hexNumber[HEX_BUF_SIZE], char decNumber[DEC_BUF_SIZE]) {
    uint16_t decimal = getDecimal(hexNumber);
    decimal = snprintf(decNumber, DEC_BUF_SIZE, "%u,", decimal);
}

int movePaddingToBeginning(FILE** file, int originalFileSize) {
    fseek(*file, -4, SEEK_END); /*4 caracteres hexa*/
    int writePosition = ftell(*file);
    int readPosition = originalFileSize - 4;
    char hexNumber[HEX_BUF_SIZE];
    memset(hexNumber, 0, HEX_BUF_SIZE);

    fseek(*file, readPosition, SEEK_SET);
    fread(hexNumber, sizeof(char), HEX_BUF_SIZE, *file);
    readPosition -= 4;

    while (readPosition != -8) { /*condicion de corte para cuando termine de escribir el primer numero*/
        fseek(*file, writePosition, SEEK_SET);
        fwrite(hexNumber, sizeof(char), HEX_BUF_SIZE, *file);
        writePosition -= 4;
        fseek(*file, readPosition, SEEK_SET);
        fread(hexNumber, sizeof(char), HEX_BUF_SIZE, *file);
        readPosition -= 4;
    }

    return writePosition + 4;
}

int main() {
    const char* fileName = "numeros.txt";
    FILE* file = fopen(fileName, "r+");

    if (!file) return 1;

    char hexNumber[HEX_BUF_SIZE];
    char decNumber[DEC_BUF_SIZE];
    memset(hexNumber, 0, HEX_BUF_SIZE);
    memset(decNumber, 0, DEC_BUF_SIZE);

    fseek(file, 0, SEEK_END);

    int fileSize = ftell(file);
    int amountOfNumbers = fileSize / 4;
    int extraBytes = amountOfNumbers * (DEC_BUF_SIZE - 1) - fileSize; /*calculo el tamanio maximo que podria tener el archivo cuando reemplazo por decimales con separador , y en base a eso lo que tengo que agreagar*/
    char padding = 'a';

    for (int i = 0; i < extraBytes; ++i) {
        fwrite(&padding, sizeof(char), 1, file); /*escribo el padding*/
    }

    int readPosition = movePaddingToBeginning(&file, fileSize); /*corro el archivo original hacia el final cosa que quede la basura al principio*/
    int writePosition = 0;

    fseek(file, readPosition, SEEK_SET);
    fseek(file, 0, SEEK_SET);
    fread(hexNumber, sizeof(char), HEX_BUF_SIZE, file);
    readPosition += 4;

    while (!feof(file)) {
        hexToDec(hexNumber, decNumber);
        fseek(file, writePosition, SEEK_SET);
        fwrite(decNumber, sizeof(char), strlen(decNumber), file);
        writePosition += strlen(decNumber);
        fseek(file, readPosition, SEEK_SET);
        fread(hexNumber, sizeof(char), HEX_BUF_SIZE, file);
        readPosition += 4;
    }

    ftruncate(fileno(file), writePosition);

    fclose(file);

    return 0;
}