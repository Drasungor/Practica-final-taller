/*Escribir un programa ISO C que reciba por argumento el nombre de un archivo de
texto y lo procese sobre si mismo (sin crear archivos intermedios ni subiendo
todo su contenido a memoria). El procesamiento consiste en eliminar las lineas
de 1 sola palabra.*/

/*Me tomo la libertad de asumir que no hay cosas mala leche como varios espacios al final
que no separan palabras, basicamente porque esto implica muchas complicaciones y no me da
el tiempo*/

#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

#define PARTIAL_LINE_SPACE_FOUND -2
#define PARTIAL_LINE_SPACE_NOT_FOUND -1

#define BUF_SIZE 32

void deleteLine(FILE* file, FILE* aux, int startOffset, char* fileName) { /*startOffset es desde donde empiezo a copiar todo*/
    fseek(aux, startOffset, SEEK_SET);
    char charRead = fgetc(file);

    while (charRead != EOF) {
        fputc(charRead, aux);
        charRead = fgetc(file);
    }

    ftruncate(fileno(aux), ftell(aux)); /*borro lo que sobra*/
    fflush(aux); /*escribo cambios a disco*/
    fclose(file);
    file = fopen(fileName, "r+"); /*actualizamos file*/
}

int processLine(char buffer[BUF_SIZE], FILE* file, FILE* aux, int position, char* fileName) {
    if (strstr(buffer, "\n")) { /*si encontre el \n, es decir si lei la linea entera*/
        if (!strstr(buffer, " ")) { /*veo si hay un espacio, ver despues que hago si hay una sola palabra y muchos espacios*/

            deleteLine(file, aux, position, fileName);
            fseek(file, position, SEEK_SET);

        }
    } else {
        if (strstr(buffer, " ")) {
            return PARTIAL_LINE_SPACE_FOUND; /*esto me dice que hay mas de una palabra ya en la linea*/
        }
        return PARTIAL_LINE_SPACE_NOT_FOUND; /*indica que no termine de leer la linea y no encontre mas de una palabra todavia*/
    }
    return 0;
}

void ignoreLine(char buffer[BUF_SIZE], FILE* file) {
    do {
        fgets(buffer, BUF_SIZE, file);
    } while(!strstr(buffer, "\n"));
}

int main(int argc, char** argv) {
    char* fileName = argv[1];
    FILE* file = fopen(fileName, "r+"); /*lectura*/
    FILE* aux = fopen(fileName, "r+"); /*escritura*/
    if (!file || !aux) return -1;

    char buffer[BUF_SIZE]; /*Buffer para ir leyendo*/
    int position = 0; /*byte en el que empiiza en el archivo la linea que acabo de leer para asi poder borrarla en caso de que sea necesario*/
    fgets(buffer, BUF_SIZE, file); /*fgets lee BUF_SIZE - 1 bytes/caracteres ya que pone el /0 al final*/

    while (!feof(file)) {
        int result = processLine(buffer, file, aux, position, fileName);
        if (result == 0) {
            position = ftell(file);
        } else if (result == PARTIAL_LINE_SPACE_FOUND) {
            ignoreLine(buffer, file);
            position = ftell(file);
        }
        fgets(buffer, BUF_SIZE, file);
    }


    /*procesar una vez*/
    processLine(buffer, file, aux, position, fileName);

    fclose(file);
    fclose(aux);

    return 0;
}
