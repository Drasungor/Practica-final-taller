/*4)
Escriba una funcion C llamada Agrandar que reciba por parametro 1 cadena (S),

dos indices (I1, I2) y una cantidad (Q).

La funcion debe retornar una copia de S salvo los caracteres entre los indices

I1 y I2 que seran duplicados Q veces en la misma posicion.

Ej: Agrandar("Chau", 1, 2, 3) retorna "Chahahau"*/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>


/*Si la funcion recibe cosas como el orto retorna NULL*/
char* Agrandar(char* S, int I1, int I2, int Q) {
    if (Q == 1) return S;
    if (Q < 1 || I2 < I1) return NULL;
    int sizeS = strlen(S); //no cuento el /0
    if (I2 > sizeS) return NULL; //chequeo de errores

    sizeS += (I2 - I1 + 1)*(Q - 1); //-1 xq sino cuento una vez mas el original porque ya lo conte en strlen(S)
    char* nS = malloc(sizeof(char)*(sizeS + 1)); //+1 por el \0
    if (!nS) return NULL; //chequeo de errores
    memset(nS, 0, sizeof(char)*(sizeS + 1));

    char charRead = -1;
    int i = 0, l = 0;

    charRead = S[i]; //es lo mismo que S[0]
    while (charRead != '\0') {
        if (i == I1) {
            for (int j = 0; j < Q; ++j) {
                for (int k = I1; k <= I2; ++k) {
                    nS[l] = S[k];
                    ++l;
                }
            }
            i = I2;
        } else {
            nS[l] = charRead;
            ++l;
        }
        ++i;
        charRead = S[i];
    }

    nS[l] = charRead; //le asigno el \0

    return nS;
}

int main() {
    char* word = "Chau";
    char* newWord = Agrandar(word, 1, 2, 3);
    printf("%s\n", newWord);
    free(newWord);

    return 0;
}
