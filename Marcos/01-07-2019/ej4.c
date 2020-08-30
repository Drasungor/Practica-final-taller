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

#define BUF_SIZE 512

void deleteLine(FILE* file, FILE* aux, int startOffset, char* fileName) { /*startOffset es desde donde empiezo a copiar todo*/
    fseek(aux, startOffset, SEEK_SET);
    char charRead = fgetc(file);

    while (charRead != EOF) {
        printf("%d\n", startOffset);
        fputc(charRead, aux);
        charRead = fgetc(file);
    }

    ftruncate(fileno(aux), ftell(aux)); /*borro lo que sobra*/
    fflush(aux); /*escribo cambios a disco*/
    fclose(file);
    file = fopen(fileName, "r+"); /*actualizamos file*/
}

void processLine(char buffer[BUF_SIZE], FILE* file, FILE* aux, int position, char* fileName) {
    if (strstr(buffer, "\n")) { /*si encontre el \n, es decir si lei la linea entera*/
        if (!strstr(buffer, " ")) { /*veo si hay un espacio, ver despues que hago si hay una sola palabra y muchos espacios*/

            //printf("%s", buffer);
            deleteLine(file, aux, position, fileName);
            fseek(file, position, SEEK_SET);

        }
    }
}

int main(int argc, char** argv) {
    char* fileName = argv[1];
    FILE* file = fopen(fileName, "r+"); /*lectura*/
    FILE* aux = fopen(fileName, "r+"); /*escritura*/
    if (!file || !aux) return -1;

    char buffer[BUF_SIZE]; /*Buffer para ir leyendo*/
    int position = 0;
    fgets(buffer, BUF_SIZE, file); /*fgets lee BUF_SIZE - 1 bytes/caracteres ya que pone el /0 al final*/
    //printf("%s\n", buffer);

    while (!feof(file)) {
        processLine(buffer, file, aux, position, fileName);
        position = ftell(file);
        fgets(buffer, BUF_SIZE, file);
    }


    /*procesar una vez*/
    processLine(buffer, file, aux, position, fileName);

    fclose(file);
    fclose(aux);

    return 0;
}
