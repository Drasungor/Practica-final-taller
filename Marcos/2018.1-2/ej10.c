/*10) Escriba una funcion de C llamada strncat_new que reciba tres parametros:
dos punteros a caracter constante (S1 y S2) y un entero sin signo (L).

La funcion debe concatenar S1 con S2 y retornar una nueva cadena de caracteres
considerando L como tamaño maximo para cualquiera de los elementos (S1, S2 y
la nueva cadena).

La funcion debe detectar condiciones de error respecto de la longitud y retornar
NULL en cualquier caso.*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

char* strncat_new(char* S1, char* S2, int L) {
    if (!S1 || !S2 || L < 0) {
        return NULL;
    }

    int sizeS1 = strlen(S1);
    int sizeS2 = strlen(S2);

    int resultSize = sizeS1 + sizeS2 + 1; //+1 por el \0
    if (L < resultSize) {
        return NULL;
    }

    char* result = malloc(sizeof(char)*resultSize);
    if (!result) {
        return NULL; //chequeo si malloc fallo, la verdad que no falla nunca pero bueno qsy
    }

    memset(result, 0, resultSize);
    memcpy(result, S1, sizeS1);
    memcpy(result + sizeS1, S2, sizeS2);

    return result;
}

int main() {
    char* s1 = "Hola bro como andas";
    char* s2 = "Todo piola kpo y vos";
    char* result = strncat_new(s1, s2, 25);
    if (result) {
        printf("%s\n", result);
        free(result);
    }
    return 0;
}