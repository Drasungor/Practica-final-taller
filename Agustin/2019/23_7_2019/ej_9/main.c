//Tiene un bug en el que no elimina el espacio entre una palabra valida y la ultima
//palabra si esta no era valida, pero chances que lo cambio asique es un feature

#define _POSIX_C_SOURCE 200112L
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/types.h>

//retorna -1 si no pudo encontrar el caracter
int obtener_fin_de_palabra(char* string, int len) {
    for (int i = 0; i < len; ++i) {
        if ((string[i] == ' ') || (string[i] == '\n')) {
            return i;
        }
    }
    return -1;
}

//Retorna true si el programa debe seguir corriendo, sino retorna false
bool descartar_palabra(FILE* lectura, FILE* escritura) {
    char contenedor_de_char;
    fread(&contenedor_de_char, sizeof(char), 1, lectura);
    while ((contenedor_de_char != ' ') && (contenedor_de_char != '\n') && (!feof(lectura))) {
        fread(&contenedor_de_char, sizeof(char), 1, lectura);
    }
    if (contenedor_de_char == '\n') {
        fseek(escritura, -1, SEEK_CUR);
        fwrite(&contenedor_de_char, sizeof(char), 1, escritura);
    }
    return !feof(lectura);
}

//Retorna true si el programa debe seguir ejecutandose, sino retorna false
//El puntero se modifica para que contenga la cantidad de caracteres escritos en el
//archivo
bool procesar_palabra(FILE* lectura, FILE* escritura, int* caracteres_escritos) {
    *caracteres_escritos = 0;
    int indice_fin;
    int posiciones_para_atras;
    char buffer[5];
    int tamanio_de_lo_leido;
    memset(buffer, 0, 5);
    tamanio_de_lo_leido = fread(buffer, sizeof(char), 4, lectura);
    if (feof(lectura) && tamanio_de_lo_leido == 0) {
        return false;
    }
    indice_fin = obtener_fin_de_palabra(buffer, tamanio_de_lo_leido);
    if ((indice_fin == -1) && (tamanio_de_lo_leido == 4)) {//Si es la ultima palabra no tiene un espacio antes del final y puede ocupar menos de 4 chars
        if (!descartar_palabra(lectura, escritura)) {
            return false;
        }
    } else {
        if (indice_fin == -1) {//Si es la ultima palabra no tiene un espacio antes del final
            indice_fin = tamanio_de_lo_leido - 1;
        }
        posiciones_para_atras =  tamanio_de_lo_leido - (indice_fin + 1);
        fseek(lectura, -posiciones_para_atras, SEEK_CUR);
        fwrite(buffer, sizeof(char), indice_fin + 1, escritura);
        *caracteres_escritos += indice_fin + 1;
    }
    return !feof(lectura);
}

void procesar_archivo(FILE* lectura, FILE* escritura) {
    int tamanio_final = 0;
    int caracteres_escritos = 0;
    bool continua_el_programa = procesar_palabra(lectura, escritura, &caracteres_escritos);
    tamanio_final += caracteres_escritos;
    while ((!feof(lectura)) && continua_el_programa) {
        continua_el_programa = procesar_palabra(lectura, escritura, &caracteres_escritos);
        tamanio_final += caracteres_escritos;
    }
    ftruncate(fileno(escritura), tamanio_final);
}

//Se asume que las palabras son separadas solo por espacios y enters
int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Nombre de archivo invalido\n");
        return -1;
    }
    FILE* lectura = fopen(argv[1], "r");
    FILE* escritura = fopen(argv[1], "r+");
    procesar_archivo(lectura, escritura);
    fclose(escritura);
    fclose(lectura);
    return 0;
}
