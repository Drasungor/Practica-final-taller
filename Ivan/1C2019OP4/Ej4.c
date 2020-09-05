#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/types.h>

#include <arpa/inet.h>
void eliminar(FILE** file) {
    uint16_t currNum;
    clearerr(*file);
    fread(&currNum, sizeof(uint16_t), 1, *file);

    while (!feof(*file)) {
        currNum = ntohs(currNum);

        fseek(*file, -2*sizeof(uint16_t), SEEK_CUR);
        currNum = htons(currNum);
        fwrite(&currNum, sizeof(uint16_t), 1, *file);
        fseek(*file, sizeof(uint16_t), SEEK_CUR);
        fread(&currNum, sizeof(uint16_t), 1, *file);
    }
    fseek(*file, 0, SEEK_END);
    long file_size = ftell(*file);
    ftruncate(fileno(*file), file_size - sizeof(uint16_t));
}


int main(int argc, char const *argv[]) {
    FILE* file = fopen(argv[1], "rb+");
    if(!file) return -1;

    uint16_t currNum;
    long read_pos;
    int elim = 0;

    fread(&currNum, sizeof(uint16_t), 1, file);

    while (!feof(file)) {
        printf("%d\n", currNum);
        currNum = ntohs(currNum);
        if ((currNum % 7) == 0) {
            ++elim;
            read_pos = ftell(file) - sizeof(uint16_t);
            eliminar(&file);
            fseek(file, read_pos, SEEK_SET);
        }
        fread(&currNum, sizeof(uint16_t), 1, file);
    }

    fclose(file);
    return 0;
}
