/*2) Implemente la funcion void String_a_Int(char *bin, int *ent) que interprete la
cadena bin (de 32 1s/0s) y guarde el valor correspondiente en el entero indicado por ent.*/

/*Asumo cadena binaria en big endian*/


#include <math.h>
#include <stdio.h>
#define BIT_LEN 32

void String_a_Int(char* bin, int* ent) {
    *ent = 0;
    for (int i = 0; i < BIT_LEN; ++i) {
        if (bin[i] == '1') {
            (*ent) += pow(2, BIT_LEN - i - 1);
        }
    }
}

int main() {
    int ent = 0;
    char bin[32] = {'0','1','0','0','1','1','0','1','1','0','1','1','1','0','1','0','0','1','0','0','1','0','1','0','0','1','0','1','1','0','1','1'};
    String_a_Int(bin, &ent);
    printf("%d\n", ent);
    return 0;
}