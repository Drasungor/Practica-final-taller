#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

void execute_program(FILE* write, FILE* read) {
    int final_number_of_chars = 0;
    char first_read;
    char second_read;
    fread(&first_read, sizeof(char), 1, read);
    while (!feof(read)) {
        fread(&second_read, sizeof(char), 1, read);
        while ((second_read == first_read) && (!feof(read))) {
            fread(&second_read, sizeof(char), 1, read);
        }
        fwrite(&first_read, sizeof(char), 1, write);
        final_number_of_chars++;
        if (!feof(read)) {
            first_read = second_read;
        }
    }
    ftruncate(fileno(write), final_number_of_chars);
}


int main(int argc, char* argv[]) {
    if (argc != 2) {
        return -1;
    }
    FILE* write = fopen(argv[1], "r+");
    if (!write) {
        return -1;
    }
    FILE* read = fopen(argv[1], "r");
    if (!read) {
        fclose(write);
        return -1;
    }
    execute_program(write, read);
    fclose(read);
    fclose(write);
    return 0;
}
