
#include <stdio.h>
#include <string.h>
#include<stdlib.h>

int main(int argc, char const *argv[]) {
    char* sentence = argv[1];
    char* word = argv[2];
    char* reemp = malloc(2*strlen(argv[1]));
    memset(reemp,0,2*strlen(argv[1]));
    printf("Sentence: %s\n", sentence);
    printf("Word: %s\n", word);

    int word_start_index = 0;
    int last_index = 0;
    int curr_index = 0;
    char* word_start = strstr(sentence, word);
    char* aux = sentence;

    while (word_start != NULL) {
        //Escribo todo hasta donde empieza Word
        while (aux != word_start) {
            reemp[curr_index] = *aux;
            ++curr_index;
            ++aux;
        }
        //Escribo Word dos veces
        for (size_t i = 0; i < strlen(word); i++) {
            reemp[curr_index] = word[i];
            ++curr_index;
            ++aux;
        }
        for (size_t i = 0; i < strlen(word); i++) {
            reemp[curr_index] = word[i];
            ++curr_index;
        }
        word_start = strstr(aux, word);
    }
    //Escribo lo que va despues de Word
    while (*aux != '\0') {
        reemp[curr_index] = *aux;
        ++curr_index;
        ++aux;
    }

    for (size_t i = 0; i < strlen(reemp); i++) {
        printf("%c", *(reemp + i));
    }
    printf("\n");
    free(reemp);
    return 0;
}
