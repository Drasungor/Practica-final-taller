#define _POSIX_C_SOURCE 200112L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdbool.h>


//Agrega la basura al archivo y la deja al principio de este
void add_garbage(FILE* write, int garbage_size, int initial_size) {
    char aux = 0;
    for (int i = 0; i < garbage_size; ++i) {
        fwrite(&aux, sizeof(char), 1, write);
    }
    for (int i = 0; i < initial_size; ++i) {
        fseek(write, -garbage_size-1-i, SEEK_END);
        fread(&aux, sizeof(char), 1, write);
        fseek(write, -1-i, SEEK_END);
        fwrite(&aux, sizeof(char), 1, write);
    }
}

bool execute_program(FILE* write, const char* file_name) {
    fseek(write, 0, SEEK_END);
    int file_size = ftell(write);
    int numbers_amount = file_size/4;
    int max_final_size = 6 * numbers_amount;//Cada numero puede ocupar 5 digs + la coma separadora
    int final_size = 0;
    char hexa_buf[5];
    char dec_buf[6];
    char separator = ',';
    int dec_version, dec_buf_len;
    memset(hexa_buf, 0, 5);
    memset(dec_buf, 0, 6);
    add_garbage(write, max_final_size - file_size, file_size);
    fseek(write, 0, SEEK_SET);
    FILE* read = fopen(file_name, "r");
    if (!read) {
        return false;
    }
    fseek(read, max_final_size - file_size, SEEK_SET);
    for (int i = 0; i < numbers_amount; ++i) {
        fread(hexa_buf, sizeof(char), 4, read);
        dec_version = strtol(hexa_buf, NULL, 16);
        sprintf(dec_buf, "%d", dec_version);//Nunca va a ser mas grande que un int porque los hexa son de 4 digitos
        dec_buf_len = strlen(dec_buf);
        fwrite(dec_buf, sizeof(char), dec_buf_len, write);
        fwrite(&separator, sizeof(char), 1, write);
        final_size += dec_buf_len + 1;
    }
    fclose(read);
    ftruncate(fileno(write), final_size);
    return true;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        return -1;
    }
    FILE* write = fopen(argv[1], "r+");
    if (!write) {
        return -1;
    }
    bool program_status = execute_program(write, argv[1]);
    fclose(write);
    if (!program_status) {
        return -1;
    }
    return 0;
}
