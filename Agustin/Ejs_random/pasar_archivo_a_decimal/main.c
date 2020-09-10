#define _POSIX_C_SOURCE 200112l
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

//Se asume que el archivo no termina con \n


//Agrega la basura en el archivo y la deja al principio de este, desplazando
//el contenido hacia abajo

void execute_program(FILE* write) {
    fseek(write, 0, SEEK_END);
    int file_size = ftell(write);
    int numbers_amount = file_size / 4;
    int max_size = numbers_amount * 6;
    int garbage_size = max_size - file_size;
    char garbage = 0;
    char dec_buf[6];//5 digitos + \0
    char hexa_buf[5];//4 digitos + \0
    int dec_ver;
    int dec_len;
    int number_of_chars = 0;
    char separator = ',';
    memset(dec_buf, 0, 7);
    memset(hexa_buf, 0, 6);
    fseek(write, 0, SEEK_END);
    for (int i = 0; i < garbage_size; ++i) {
        fwrite(&garbage, sizeof(char), 1, write);
    }
    for (int i = 0; i < file_size; ++i) {
        fseek(write, file_size - 1 - i, SEEK_SET);
        fread(&garbage, sizeof(char), 1, write);
        fseek(write, max_size - 1 - i, SEEK_SET);
        fwrite(&garbage, sizeof(char), 1, write);
    }
    for (int i = 0; i < numbers_amount; ++i) {
        fseek(write, garbage_size + 4 * i, SEEK_SET);
        fread(hexa_buf, sizeof(char), 4, write);
        dec_ver = strtol(hexa_buf, NULL, 16);//tiene que entrar en un int
        sprintf(dec_buf, "%d", dec_ver);
        dec_len = strlen(dec_buf);
        fseek(write, number_of_chars, SEEK_SET);
        fwrite(dec_buf, sizeof(char), dec_len, write);
        fwrite(&separator, sizeof(char), 1, write);
        number_of_chars += dec_len + 1;
    }
    ftruncate(fileno(write), number_of_chars);
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Cantidad de parametros incorrecta\n");
        return -1;
    }
    FILE* write = fopen(argv[1], "r+");
    if (!write) {
        fprintf(stderr, "Archivo inexistente\n");
        return -1;
    }
    execute_program(write);
    fclose(write);
    return 0;
}
