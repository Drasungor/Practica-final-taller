/*Escriba un programa C que tome 2 cadenas por linea de comandos: A y B;
e imprima la cadena A despues de haber duplicado todas las ocurrencias de B.
ej: reemp.exe "Este es el final" final ------> Este es el final final*/

#include <string.h>
#include <stdio.h>

void printSoFar(char* sentence, char* appearanceLocation) {
    while (sentence != appearanceLocation) {
        printf("%c", *sentence);
        ++sentence;
    }
}

void printDuplicateKeyword(char* keyword) {
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < strlen(keyword); ++j) {
            printf("%c", keyword[j]);
        }
        if (i == 0) {
            printf(" ");
        }
    }
}

char* getNextOccurrence(char* sentence, char* keyword) {
    char* currAppearance = strstr(sentence, keyword);
    if (!currAppearance) {
        return NULL;
    } else {
        if (currAppearance == sentence && *(currAppearance + strlen(keyword)) == ' ') {
            return currAppearance;
        } else if (*(currAppearance - 1) == ' ' && ( *(currAppearance + strlen(keyword)) == ' ' ||
                                                    *(currAppearance + strlen(keyword)) == '\0') ) {
            return currAppearance;
        } else {
            return NULL;
        }
    }
}

int main (int argc, char** argv) {

    if (argc < 3) return 1;
    char* sentence = argv[1];
    char* keyword = argv[2];

    char* currAppearance = getNextOccurrence(sentence, keyword);

    char* currentPosition = sentence;

    while (currAppearance != NULL) {
        printSoFar(currentPosition, currAppearance);
        printDuplicateKeyword(keyword);
        currentPosition = currAppearance + strlen(keyword);
        currAppearance = getNextOccurrence(currentPosition, keyword);
    }

    printf("%s\n", currentPosition);

    return 0;
}