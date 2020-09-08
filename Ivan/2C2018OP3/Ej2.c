#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* Replicar(const char* string, int i1, int i2, int cant) {
    char* result = malloc(strlen(string) + (i2-i1+1)*cant + 1);
    memset(result, 0, strlen(string) + (i2-i1+1)*cant + 1);
    memcpy(result, string, i1);//Copio hasta donde empieza la palabra

    for (size_t i = 0; i < cant; i++) {
        memcpy(result + i1 + (i2-i1+1)*i, string + i1, i2 - i1 + 1);//Copio cant veces lo q esta entre indices
    }
    memcpy(result + (i2-i1+1)*cant, string + i2, strlen(string) - i2);//Copio lo q esta despues de i2
    return result;
}


int main(int argc, char** argv) {
    char* string = "Chau";
    char* result;
    result = Replicar(string, 1, 2, 3);
    printf("%s\n", result);
    free(result);
}
