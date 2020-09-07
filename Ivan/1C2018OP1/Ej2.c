/*Implemente la funcion void String_a_Int(char *bin, int *ent)
 que interprete la cadena bin (de 32 1s/0s) y guarde el valor
  correspondiente en el entero indicado por ent.*/

#include <math.h>
#include <stdio.h>

void String_a_Int(char* bin, int* ent) {
    *ent = 0;
    for (size_t i = 0; i < 32; i++) {
        *ent += bin[i] * pow(2, 31-i);
    }
}

int main(int argc, char** argv) {
    char bin[32] = {0,1,0,0,1,1,0,1,1,0,1,1,1,0,1,0,0,1,0,0,1,0,1,0,0,1,0,1,1,0,1,1};
    int ent;

    String_a_Int(bin, &ent);

    printf("%d\n", ent);

    return 0;
}
