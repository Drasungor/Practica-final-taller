/*6) Escriba una funcion ISO C que permita procesar un archivo texto sobre si
mismo, que contenga una palabra por linea. El procesamiento consiste en odenar
las palabras (lineas) alfabeticamente considerando que el archivo no entra
en memoria.*/

/*La ultima palabra tiene que tener \n por ahora, despues veo como arreglarlo*/
/*Update: es una paja cambiar eso, es un feature*/
/*Asumo que no hay palabras repetidas*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define DEFAULT_WORD_SIZE 32

char* getNextWord(FILE** file, int readPosition) {
    int wordSize = DEFAULT_WORD_SIZE;
    int i = 1;
    char* word = NULL; /*reservo mi buffer inicial*/
    char* aux = NULL;

    do {
        free(word); /*free(NULL) no hace nada asi que la primera vez no va a pasar nada*/
        word = malloc(sizeof(char)*DEFAULT_WORD_SIZE*i);
        fseek(*file, readPosition, SEEK_SET);
        if (!fgets(word, DEFAULT_WORD_SIZE*i, *file)) {
            free(word);
            return NULL; /*alcance EOF, no hay mas palabras*/
        }
        ++i; /*La siguiente vez voy a pedir el doble de memoria y asi hasta que me entre toda la palabra*/
    } while (!strstr(word, "\n")); /*si no logre leer toda la palabra, es decir, no encontre el \n*/

    return word;
}

void switchWords(FILE** file, char* word, char* nextWord) {
    fseek(*file, -(strlen(word) + strlen(nextWord)), SEEK_CUR);
    fputs(nextWord, *file);
    fputs(word, *file); /*switcheo las palabras entre si*/
}

int main(int argc, const char** argv) {
    if (argc < 2) return 1;
    const char* fileName = argv[1];

    bool isSorted;
    FILE* file = fopen(fileName, "r+"); /*podria abrirlo en binario y leer a pulmon pero prefiero usar fgets que lee hasta al el \n*/
    if (!file) return 1;

    char* word = NULL;
    char* nextWord = NULL;

    do { /*bubble sort FTW*/
        isSorted = true;
        fseek(file, 0, SEEK_SET);
        free(word);
        free(nextWord);
        word = getNextWord(&file, ftell(file));
        nextWord = getNextWord(&file, ftell(file));

        while (nextWord != NULL) {
            if (strcmp(word, nextWord) < 0) { /*s1 es alfabeticamente mayor a s2*/
                free(word);
                word = nextWord;
            } else {
                switchWords(&file, word, nextWord);
                free(nextWord);
                isSorted = false;
            }

            nextWord = getNextWord(&file, ftell(file));
        }

    } while (!isSorted);

    free(word);
    fclose(file);

    return 0;
}