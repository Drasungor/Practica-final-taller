#include<math.h>
#include <stdio.h>
#include <string.h>


int charToInt(char digito) {
    if ((digito >= '0') && (digito <= '9')) {
        return 0 + digito - '0';
    } else {
        return 10 + digito - 'A';
    }
}

void ValorHex(char* hex, int* dec) {
    *dec = 0;
    for (size_t i = 0; i < strlen(hex); i++) {
        *dec += charToInt(hex[i]) * pow(16, 3-i);
    }
}


int main(int argc, char** argv) {
    char hex[4] = {'A', 'A', '4', '3'};
    int dec = 0;
    ValorHex(hex, &dec);
    printf("%d\n", hex[2]);
    printf("%d\n", dec);
    return 0;
}
