#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

//Asumo que todas las palabras terminan en \n y que no hay lineas vacias


bool resize(char** curr_buff, int* buff_size) {
    char* aux_ptr;
    aux_ptr = realloc(*curr_buff, (*buff_size) * 2);
    if (!aux_ptr) {
        return false;
    }
    *curr_buff = aux_ptr;
    (*buff_size) = (*buff_size) * 2;
    return true;
}

bool add_char(char c, char** curr_buff, int* buff_size, int* chars_amount) {
    (*curr_buff)[(*chars_amount)] = c;
    (*chars_amount)++;
    if (*buff_size == *chars_amount) {
        if (!resize(curr_buff, buff_size)) {
            return false;
        }
    }
    return true;
}

bool get_line(FILE* file, char** curr_buff, int* buff_size) {
    char aux;
    int chars_amount = 0;
    fread(&aux, sizeof(char), 1, file);
    memset(*curr_buff, 0, *buff_size);
    while (aux != '\n') {
        if (!add_char(aux, curr_buff, buff_size, &chars_amount)) {
            return false;
        }
        fread(&aux, sizeof(char), 1, file);
    }
    if (!add_char(aux, curr_buff, buff_size, &chars_amount)) {
        return false;
    }
    return add_char('\0', curr_buff, buff_size, &chars_amount);
}

int get_lines_amount(FILE* file) {
    char buf;
    int lines_amount = 0;
    fread(&buf, sizeof(char), 1, file);
    while (!feof(file)) {
        if (buf == '\n') {
            lines_amount++;
        }
        fread(&buf, sizeof(char), 1, file);
    }
    fseek(file, 0, SEEK_SET);
    return lines_amount;
}

void print_all_file(FILE* file) {
    char aux;
    fread(&aux, sizeof(char), 1, file);
    while (!feof(file)) {
        printf("%c", aux);
        fread(&aux, sizeof(char), 1, file);
    }
    fseek(file, 0, SEEK_SET);
}

bool sort_file(FILE* file) {
    int lines_amount = get_lines_amount(file);
    int size_1 = 8, size_2 = 8;
    char* line_1 = malloc(size_1 * sizeof(char));
    char* line_2 = malloc(size_2 * sizeof(char));
    bool return_value = true;
    int len_1, len_2;
    for (int i = 0; i < lines_amount - 1; ++i) {
        for (int j = 0; j < lines_amount - 1 - i; ++j) {
            if ((!get_line(file, &line_1, &size_1)) || ((!get_line(file, &line_2, &size_2)))) {
                return_value = false;
                break;
            }
            len_1 = strlen(line_1);
            len_2 = strlen(line_2);
            if (strcmp(line_1, line_2) < 0) {
                fseek(file, -len_2, SEEK_CUR);
            } else {
                fseek(file, -(len_1 + len_2), SEEK_CUR);
                fwrite(line_2, sizeof(char), len_2, file);
                fwrite(line_1, sizeof(char), len_1, file);
                fseek(file, -len_1, SEEK_CUR);
            }
        }
        if (!return_value) {
            break;
        }
        fseek(file, 0, SEEK_SET);
        print_all_file(file);
    }
    free(line_1);
    free(line_2);
    return return_value;
}


int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Cantidad incorrecta de parametros\n");
        return -1;
    }
    FILE* file = fopen(argv[1], "r+");
    if (!file) {
        printf("Nombre de archivo incorrecto \n");
        return -1;
    }
    bool program_status = sort_file(file);
    fclose(file);
    if (!program_status) {
        return  -1;
    }
    return 0;
}
