/*4) Escribir un programa C que procese el archivo "numeros.txt" sobre si mismo
(sin crear archivos intermedios y sin subir el archivo a memoria). El procesamiento
consiste en leer grupos de 4 caracteres hexadecimales y reemplazarlos por los
correspondientes digitos decimales (que representen el mismo numero leido pero
en decimal)*/

/*Asumo que el hexa esta en big endian (o sea escrito como la gente)*/

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <math.h>

#define HEX_BUF_SIZE 5
#define DEC_BUF_SIZE 6 /*el numero mas grande representable en unsigned con 2 bytes es (2^16 -1) = 65535*/

int getHexMultiplier(char hexSymbol) {
    int multiplier = 0;

    if ( ('0' <=  hexSymbol) && (hexSymbol <= '9') ) {
        multiplier = hexSymbol - '0';
    } else if ('A' <= hexSymbol && hexSymbol <= 'F') {
        multiplier = hexSymbol - 'A' + 10;
    }

    return multiplier;
}

uint16_t hexToDecimalInt(char hexNumber[HEX_BUF_SIZE]) {
    uint16_t decimalNumber = 0;
    int hexMultiplier = 0;

    for (int i = (HEX_BUF_SIZE - 2); i >= 0; --i) { /*no leo el /0*/
        hexMultiplier = getHexMultiplier(hexNumber[HEX_BUF_SIZE - 2 - i]);
        decimalNumber += (pow(16, i) * hexMultiplier);
    }

    return decimalNumber;
}

void hexToDecimalString(char hexNumber[HEX_BUF_SIZE], char decNumber[DEC_BUF_SIZE]) {
    uint16_t decimalNumber = hexToDecimalInt(hexNumber);
    memset(decNumber, 0, sizeof(char)*DEC_BUF_SIZE);
    snprintf(decNumber, DEC_BUF_SIZE, "%u", decimalNumber);
}

void expandFile(FILE** file, char decNumber[DEC_BUF_SIZE], int startOffset) {
    int padding = 0;
    int bytesToExpand = strlen(decNumber) - 4;
    int stopOffset = startOffset + 3;
    fseek(*file, 0, SEEK_END);
    fwrite(&padding, sizeof(char), bytesToExpand, *file);
    fflush(*file); /*escribimos los cambios a disco*/
    FILE* aux = fopen("numeros.txt", "r+"); /*uso este para ir leyendo*/
    fseek(*file, 0, SEEK_END);
    fseek(aux, -bytesToExpand, SEEK_END);

    while (ftell(aux) != stopOffset) {
        char byte = fgetc(aux);
        fputc(byte, *file);
        fseek(aux, -2*sizeof(char), SEEK_CUR);
        fseek(*file, -2*sizeof(char), SEEK_CUR);
    }

    fseek(*file, startOffset, SEEK_SET); /*copio el decimal*/

    for (int i = 0; i < DEC_BUF_SIZE; ++i) {
        if (decNumber[i] == '\0')
            break;
        fputc(decNumber[i], *file);
    }

    fclose(aux);
}

int main() {

    FILE* file = fopen("numeros.txt", "r+");
    char hexNumber[HEX_BUF_SIZE];
    char decNumber[DEC_BUF_SIZE];
    int currPosition = 0;
    memset(hexNumber, 0, sizeof(char)*HEX_BUF_SIZE);
    memset(decNumber, 0, sizeof(char)*DEC_BUF_SIZE);
    fgets(hexNumber, HEX_BUF_SIZE, file);

    while (!feof(file)) {
        hexToDecimalString(hexNumber, decNumber);
        int decLength = strlen(decNumber);
        if (decLength < 4) {
            //truncateFile();
        } else if (decLength > 4) {
            expandFile(&file, decNumber, currPosition);
        } else {
            fseek(file, currPosition, SEEK_SET);
            fwrite(decNumber, 4*sizeof(char), 1, file);
        }
        currPosition = ftell(file);
        fgets(hexNumber, HEX_BUF_SIZE, file);
    }

    fclose(file);



    return 0;
}
