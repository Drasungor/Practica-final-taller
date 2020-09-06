#include <stdio.h>
#include <stdbool.h>
#include <string.h>

//Retorna el indice del siguiente caracter al ultimo caracter de la primera instancia de
//la palabra buscada
//Si no se encuentra una instancia retorna -1
int after_word_index(const char source[], int source_len, const char searched_string[], int searched_string_len) {
    if ((source_len <= 0) || (searched_string_len <= 0)) {
        return -1;
    }
    bool was_found = true;
    for (int i = 0; i < (source_len - searched_string_len + 1); ++i) {
        for (int j = 0; j < searched_string_len; ++j) {
            if (source[i + j] != searched_string[j]) {
                was_found = false;
                break;
            }
        }
        if (was_found) {
            return i + searched_string_len;
        }
        was_found = true;
    }
    return -1;
}

int main(int argc, const char* argv[]) {
    if (argc != 3) {
        printf("Cantidad de parametros invalida\n");
        return -1;
    }
    int source_word_len = strlen(argv[1]);
    int searched_word_len = strlen(argv[2]);
    int last_index = 0;
    int new_index = after_word_index(argv[1], source_word_len, argv[2], searched_word_len);
    int original_printed_chars = 0;
    while (new_index != -1) {
        for (int i = last_index; i < new_index; ++i) {
            printf("%c", argv[1][i]);
            original_printed_chars++;
        }
        for (int i = 0; i < searched_word_len; ++i) {
            printf("%c", argv[2][i]);
        }
        last_index = new_index;
        new_index = after_word_index(argv[1] + new_index, source_word_len - original_printed_chars, argv[2], searched_word_len);
    }
    if (last_index < source_word_len) {
        printf("%s\n", argv[1] + last_index);
    }
    return 0;
}
