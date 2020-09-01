/*4) Escribir un programa C que procese el archivo "numeros.txt" sobre si mismo
(sin crear archivos intermedios y sin subir el archivo a memoria). El procesamiento
consiste en leer grupos de 4 caracteres hexadecimales y reemplazarlos por los
correspondientes digitos decimales (que representen el mismo numero leido pero
en decimal)*/

/*Asumo que el hexa esta en big endian (o sea escrito como la gente)*/

#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define HEX_BUF_SIZE 5

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

    for (int i = (HEX_BUF_SIZE - 2); i >= 0, --i) { /*no leo el /0*/
        hexMultiplier = getHexMultiplier(hexNumber[HEX_BUF_SIZE - 2 - i]);
        decimalNumber += 16^i * hexMultiplier;
    }

    return decimalNumber;
}

void hexToDecimalString(char hexNumber[HEX_BUF_SIZE]) {
    uint16_t decimalNumber = hexToDecimalInt(hexNumber);
    printf("%d\n", decimalNumber);
}

int main() {

    FILE* file = fopen("numeros.txt", "r+");
    char hexNumber[HEX_BUF_SIZE];
    memset(hexNumber, 0, sizeof(char)*HEX_BUF_SIZE);
    fgets(hexNumber, HEX_BUF_SIZE, file);

    while (!feof(file)) {
        hexToDecimalString(hexNumber);
        fgets(hexNumber, HEX_BUF_SIZE, file);
    }










    return 0;
}
