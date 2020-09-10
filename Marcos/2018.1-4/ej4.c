/*4) Escriba una funcion C llamada Agrandar que reciba por parametro 1 cadena (S),
dos indices (I1, I2) y una cantidad (Q).
La funcion debe retornar una copia de S salvo los caracteres entre los indices
I1 y I2 que seran duplicados Q veces en la misma posicion.
Ej: Agrandar("Chau", 1, 2, 3) retorna "Chahahau"*/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

char* Agrandar(const char* S, int I1, int I2, int Q) {
    if (I1 < 0 || Q < 0 || S == NULL) {
        return NULL;
    }
    int strLength = strlen(S);
    if (I2 > (strLength - 1)) {
        return NULL;
    }
    int intervalLength = I2 - I1 + 1;
    int newSLength = strLength + (intervalLength)*(Q - 1);
    char* newS = malloc(sizeof(char)*(newSLength + 1)); //+1 para el \0
    if (!newS) {
        return NULL; //fallo malloc
    }
    memset(newS, 0, newSLength + 1);
    memcpy(newS, S, I1);
    char* aux = newS + I1;
    for (int i = 0; i < Q; ++i) {
        memcpy(aux, S + I1, intervalLength);
        aux += (intervalLength);
    }
    memcpy(aux, S + I2 + 1, strLength - I2 - 1);

    return newS;
}

int main() {
    char* result = Agrandar("Hola", 1, 2, 3);
    printf("%s\n", result);
    free(result);
    return 0;
}