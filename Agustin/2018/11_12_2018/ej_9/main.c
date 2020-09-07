#include <stdio.h>
#include <string.h>

//Se asume que cualquier char es un digito valido en hexa
int valorDecimal(char digito) {
	if ((digito >= '0') && (digito <= '9')) {
		return digito - '0';
	} else {
		return 10 + digito - 'A';
	}
}

int potenciar(int base, int exponente) {
	int ret = 1;
	for (int i = 0; i < exponente; i++) {
		ret *= base;
	}
	return ret;
}

void valorHex(char* hex, int* ent) {
	int cant_digitos = strlen(hex);
	*ent = 0;
	for (int i = 0; i < cant_digitos; i++) {
		*ent += valorDecimal(hex[i]) * potenciar(16, cant_digitos -1 - i);
	}
}


int main() {
    int dec;
    valorHex("A", &dec);
    printf("A: %d\n", dec);
    return 0;
}
