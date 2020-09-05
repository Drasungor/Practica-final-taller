#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/types.h>

#include <arpa/inet.h>

#include <math.h>
#include<string.h>

int obtener_decimal(char digito) {
    if ((digito >= '0') && (digito <= '9')) {
        return 0 + digito - '0';
    } else {
        return 10 + digito - 'A';
    }
}

int hexToDec(char num[4]) {
    int decNum = 0;
    for (size_t i = 0; i < 4; i++) {
        decNum += obtener_decimal(num[i]) * pow(16, 3-i);
    }
    return decNum;
}

int main(int argc, char const *argv[]) {
    FILE* file = fopen(argv[1], "r+");

    if(!file) return -1;

    fseek(file, 0, SEEK_END);
    int cant_simbolos = ftell(file) - 1;
    int cant_numeros = cant_simbolos / 4;

    char filler = 0;
    for (size_t i = 0; i < cant_numeros * 5 - cant_simbolos; i++) {
        fwrite(&filler, sizeof(char), 1, file);
    }

    //Paso la basura al principio
    fseek(file, cant_simbolos, SEEK_SET);
    char curr_symbol;
    for (size_t i = 0; i < cant_simbolos + 1; i++) {
        fread(&curr_symbol, sizeof(char), 1, file);
        fseek(file, -i*sizeof(char) - 1, SEEK_END);
        fwrite(&curr_symbol, sizeof(char), 1, file);
        fseek(file, cant_simbolos - i - 1, SEEK_SET);
    }

    int pos_read = cant_numeros;//Voy a empezar a leer despues de la basura. La basura es igual a la cantidad de numerso
                                //xq cada numero son 4 simbolos y el nro maximo en decimal es 65535 q son 5 simbolos asi q
                                //solo necesito 1 byte de basura por numero
    int pos_write = 0;

    char buff[4];
    char currNum[5];
    int decNum;
    int numLen = 0;
    int finalSize = 0;
    for (size_t i = 0; i < cant_numeros; i++) {
        fseek(file, pos_read, SEEK_SET);
        fread(buff, sizeof(char), 4, file);
        pos_read += 4;
        decNum = hexToDec(buff);
        printf("%d\n", decNum);
        sprintf(currNum, "%d", decNum);
        fseek(file, pos_write, SEEK_SET);
        numLen = strlen(currNum);
        finalSize += numLen;
        fwrite(currNum, sizeof(char), numLen, file);
        pos_write += numLen;
    }

    if (finalSize < cant_numeros * 5) {
        ftruncate(fileno(file), finalSize);
    }

    fclose(file);
    return 0;
}
