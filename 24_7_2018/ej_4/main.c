#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void copy_string(char* dest, unsigned int dest_len, char* src, unsigned int src_len) {
    for (int i = 0; i < src_len; ++i) {
        dest[dest_len + i] = src[i];
    }
}

char* get_range_copy(char* string, unsigned int i1, unsigned int i2, unsigned int q) {
    unsigned int copied_part_len = i2 - i1 + 1;
    unsigned int src_string_len = strlen(string);
    char* new_string = malloc(sizeof(char) * (src_string_len + copied_part_len * (q - 1) + 1));
    if (!new_string) {
        return NULL;
    }
    unsigned int new_string_len = 0;
    for (int i = 0; i < i1; ++i) {
        new_string[i] = string[i];
    }
    new_string_len = i1;
    for (int i = 0; i < q; ++i) {
        copy_string(new_string, new_string_len, string + i1, copied_part_len);
        new_string_len += copied_part_len;
    }
    for (int i = 0; i < (src_string_len - i2); ++i) {
        new_string[new_string_len + i] = string[i2 + 1 + i];
    }
    new_string_len += (src_string_len - i2 - 1);
    new_string[new_string_len] = '\0';
    return new_string;
}


int main() {
    char* new_string = get_range_copy("Demn", 1, 1, 100);
    printf("%s", new_string);
    free(new_string);
}
