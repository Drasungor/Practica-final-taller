#define _POSIX_C_SOURCE 200112L
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#define DIGITS_PER_NUMBER 4

//Asumo que todos los textos de hexa estan bien, asique si no es un numero va a
//ser un caracter existente en hexadecimal (de A a F)
int obtener_decimal(char digito) {
    if ((digito >= '0') && (digito <= '9')) {
        return 0 + digito - '0';
    } else {
        return 10 + digito - 'A';
    }
}

int potencia(int base, int exponente) {
    int aux = 1;
    for (int i = 0; i < exponente; ++i) {
        aux *= base;
    }
    return aux;
}

int hexa_a_decimal(char hexa[], int largo) {
    int decimal = 0;
    for (int i = 0; i < largo; ++i) {
        decimal += obtener_decimal(hexa[i]) * (potencia(16, largo - i - 1));
    }
    return decimal;
}

void insertar_basura(FILE* archivo_lectura, int max_tamanio_final_del_archivo, int cantidad_de_caracteres) {
    char aux = 0;
    //agrando el archivo al tamaño maximo que podria tener si todos los numeros ocupan
    //5 lugares (+ la coma)
    for (int i = 0; i < max_tamanio_final_del_archivo - cantidad_de_caracteres; ++i) {
        fwrite(&aux, sizeof(char), 1, archivo_lectura);
    }

    //Muevo los caracteres para abajo, dejando la basura al principio del archivo
    for (int i = 0; i < cantidad_de_caracteres; ++i) {
        fseek(archivo_lectura, cantidad_de_caracteres - 1 - i, SEEK_SET);
        fread(&aux, sizeof(char), 1, archivo_lectura);
        fseek(archivo_lectura, max_tamanio_final_del_archivo - 1 - i, SEEK_SET);
        fwrite(&aux, sizeof(char), 1, archivo_lectura);
    }
}

//Realiza la operacion pedida sobre el archivo
void operar_sobre_el_archivo(FILE* archivo, int max_tamanio_final_del_archivo, int cantidad_de_caracteres) {
    int cantidad_final_de_chars = 0;
    int cantidad_de_numeros = cantidad_de_caracteres/DIGITS_PER_NUMBER;
    char buffer[5];
    char version_decimal[6];//5 digitos
    char separador = ',';
    int version_numero;
    int aux_len;
    int fd;
    memset(buffer, 0, 5 * sizeof(char));
    memset(version_decimal, 0, 6 * sizeof(char));
    for (int i = 0; i < cantidad_de_numeros; ++i) {
        fseek(archivo, max_tamanio_final_del_archivo - cantidad_de_caracteres + i * DIGITS_PER_NUMBER, SEEK_SET);
        fread(buffer, sizeof(char), 4, archivo);
        version_numero = hexa_a_decimal(buffer, 4);
        sprintf(version_decimal, "%d", version_numero);
        fseek(archivo, cantidad_final_de_chars, SEEK_SET);
        aux_len = strlen(version_decimal);
        fwrite(version_decimal, sizeof(char), aux_len, archivo);
        fwrite(&separador, sizeof(char), 1, archivo);
        cantidad_final_de_chars += aux_len + 1;
    }
    if (cantidad_final_de_chars < max_tamanio_final_del_archivo) {
        fd = fileno(archivo);
        ftruncate(fd, cantidad_final_de_chars);
    }
}

int main() {
    FILE* archivo_lectura = fopen("test.txt", "r+");
    if (!archivo_lectura) {
        printf("Archivo inexistente\n");
    }
    fseek(archivo_lectura, 0, SEEK_END);
    int cantidad_de_caracteres = ftell(archivo_lectura);
    int cantidad_de_numeros = cantidad_de_caracteres/DIGITS_PER_NUMBER;
    int max_tamanio_final_del_archivo = cantidad_de_numeros * 6; // 6 = cantidad maxima de digitos + caracter sepadador
    insertar_basura(archivo_lectura, max_tamanio_final_del_archivo, cantidad_de_caracteres);
    operar_sobre_el_archivo(archivo_lectura, max_tamanio_final_del_archivo, cantidad_de_caracteres);
    fclose(archivo_lectura);
    return 0;
}
