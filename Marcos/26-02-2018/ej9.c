/*9) Escribir un programa ISO C que procese el archivo de texto cuyo nombre
es recibido como parametro. El procesamiento consiste en leer oraciones y
suprimir aquellas que tengan mas de 3 palabras. Asuma que el archivo no puede
cargarse en memoria, pero una oracion si puede.*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/types.h>
#include <unistd.h>

#define SENTENCE_LEN 256

char* getNextSentence(FILE** file) {
    int startOffset = ftell(*file);
    int i = 1;
    char* s = NULL;
    char* sentence = malloc(sizeof(char)*SENTENCE_LEN*i);
    memset(sentence, 0, SENTENCE_LEN*sizeof(char));
    s = fgets(sentence, SENTENCE_LEN, *file);

    while (!strstr(sentence, "\n") && !feof(*file)) {
        ++i;
        free(sentence);
        sentence = malloc(sizeof(char)*SENTENCE_LEN*i);
        fseek(*file, startOffset, SEEK_SET);
        s = fgets(sentence, SENTENCE_LEN*i, *file);
    }

    if (s == NULL) {
        free(sentence);
    }

    return s; /*retorna sentence si encontro la oracion, NULL en caso contrario*/
}

bool sentenceMustBeDeleted(char* sentence) {
    int words = 1;
    while (sentence) {
        sentence = strstr(sentence, " ");
        if (sentence) {
            ++words;
            ++sentence; /*me salteo el espacio*/
        }
    }
    return (words > 3);
}

void deleteSentence(FILE** file, int sentenceLength) {
    int readPosition = ftell(*file);
    int writePosition = readPosition - sentenceLength;
    int offsetBackup = writePosition;

    char* word = getNextSentence(file);

    while (word) {
        fseek(*file, writePosition, SEEK_SET);
        fputs(word, *file);
        writePosition += strlen(word);
        readPosition += strlen(word);
        fseek(*file, readPosition, SEEK_SET);
        free(word);
        word = getNextSentence(file);
    }

    ftruncate(fileno(*file), writePosition);
    fseek(*file, offsetBackup, SEEK_SET);
}

int main(int argc, const char** argv) {
    if (argc < 2) return 1;
    const char* fileName = argv[1];
    FILE* file = fopen(fileName, "r+");

    char* sentence = getNextSentence(&file);

    while (sentence) {
        if (sentenceMustBeDeleted(sentence)) {
            deleteSentence(&file, strlen(sentence));
        }
        free(sentence);
        sentence = getNextSentence(&file);
    }

    fclose(file);
    return 0;
}