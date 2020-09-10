#include <stdio.h>
#include <string.h>
#include <stdlib.h>



char* Replicar(char* string, int i1, int i2, int q) {
    if ((i2 < i1) || (i2 < 0) || (q < 0)) {
        return NULL;
    }
    int string_len = strlen(string);
    int new_string_size = string_len + (q - 1) * (i2 - i1 + 1) + 1;
    int chars_escritos = 0;
    char* nuevo_string = malloc(new_string_size * sizeof(char));
    nuevo_string[new_string_size - 1] = '\0';
    for (int i = 0; i < i1; ++i) {
        nuevo_string[i] = string[i];
        chars_escritos++;
    }
    for (int i = 0; i < q; ++i) {
        for (int j = 0; j < (i2 - i1 + 1); ++j) {
            nuevo_string[chars_escritos] = string[i1 + j];
            chars_escritos++;
        }
    }
    for (int i = 0; i < (string_len - i2 - 1); ++i) {
        nuevo_string[chars_escritos] = string[i2 + i + 1];
        chars_escritos++;
    }
    return nuevo_string;
}

int main() {
    char* string = "Hola";
    char* nuevo_string = Replicar(string, 1, 2, 3);
    printf("%s: %s\n", string, nuevo_string);
    free(nuevo_string);
    return 0;
}
