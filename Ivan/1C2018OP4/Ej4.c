// Escriba una funcion C llamada Agrandar que reciba por parametro 1 cadena (S),
//
// dos indices (I1, I2) y una cantidad (Q).
//
// La funcion debe retornar una copia de S salvo los caracteres entre los indices
//
// I1 y I2 que seran duplicados Q veces en la misma posicion.
//
// Ej: Agrandar("Chau", 1, 2, 3) retorna "Chahahau"

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char* agrandar(const char* string, int start, int end, int n) {
    char* substr = malloc(end - start + 1);
    char* newString = malloc(strlen(string) + ((end - start) + 1) * (n-1) + 1);

    memcpy(substr, string + start, end - start + 1);

    memcpy(newString, string, start);

    for (size_t i = 0; i < n; i++) {//Copio la parte que quiero repetir
        memcpy(newString + start + (end - start + 1) * i, substr, end - start + 1);
    }

    memcpy(newString + start + (end - start + 1) * n, string + end + 1, strlen(string) - end);
    free(substr);
    return newString;
}

int main(int argc, char const *argv[]) {
    char* newString = agrandar("TheWayOfKings", 3, 5, 8);
    printf("%s\n",newString);
    free(newString);
    return 0;
}
