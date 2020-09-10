#define _POSIX_C_SOURCE 200112L
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdbool.h>

//Se asume que si hay un espacio le sigue otra palabra, no debe haber espacios
//entre una palabra y el \n (o despues de este) y no puede haber lineas en blanco
//El archivo debe terminar con un \n

//Lee una linea del archivo, indicando si tiene que mas de 1 palabra
bool should_be_written(FILE* read, int* read_chars, bool* has_file_ended) {
    char aux;
    *read_chars = 0;
    *has_file_ended = false;
    fread(&aux, sizeof(char), 1, read);
    if (feof(read)) {
        *has_file_ended = true;
        return false;
    }
    while (aux != '\n') {
        (*read_chars)++;
        if (aux == ' ') {
            return true;
        }
        fread(&aux, sizeof(char), 1, read);
    }
    return false;
}

int write_line(FILE* read, FILE* write, int read_chars) {
    int line_len = 0;
    char aux;
    fseek(read, -read_chars, SEEK_CUR);
    fread(&aux, sizeof(char), 1, read);
    line_len++;
    while (aux != '\n') {
        fwrite(&aux, sizeof(char), 1, write);
        fread(&aux, sizeof(char), 1, read);
        line_len++;
    }
    fwrite(&aux, sizeof(char), 1, write);
    return line_len;
}

void execute_program(FILE* write, FILE* read) {
    int number_of_chars = 0;
    int read_chars;
    bool has_file_ended = false;
    while (!has_file_ended) {
        if (should_be_written(read, &read_chars, &has_file_ended)) {
            number_of_chars += write_line(read, write, read_chars);
        }
    }
    ftruncate(fileno(write), number_of_chars * sizeof(char));
}


int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Cantidad incorrecta de parametros\n");
        return -1;
    }
    FILE* write = fopen(argv[1], "r+");
    FILE* read = fopen(argv[1], "r");
    if (!write || !read) {
        printf("Archivo inexistente\n");
        return -1;
    }
    execute_program(write, read);
    fclose(write);
    fclose(read);
    return 0;
}
