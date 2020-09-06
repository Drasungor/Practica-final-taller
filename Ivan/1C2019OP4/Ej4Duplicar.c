#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/types.h>

#include <arpa/inet.h>

void duplicar(FILE** file) {

}

int main(int argc, char const *argv[]) {
    FILE* file = fopen(argv[1], "rb+");
    if (!file) return -1;

    uint16_t currNum;
    uint16_t filler = 0;
    int mult = 0;

    fread(&currNum, sizeof(uint16_t), 1, file);
    while (!feof(file)) {
        currNum = ntohs(currNum);
        if ((currNum % 7) == 0) {
            ++mult;
        }
        fread(&currNum, sizeof(uint16_t), 1, file);
    }

    fseek(file, 0, SEEK_END);
    int last_pos = ftell(file) - sizeof(uint16_t);
    //Escribo ceros
    for (size_t i = 0; i < mult; i++) {
        fseek(file, 0, SEEK_END);
        fwrite(&filler, sizeof(uint16_t), 1, file);
    }

    fseek(file, last_pos, SEEK_SET);//me paro en el ultimo q no es 0
    for (size_t i = 0; i < last_pos/sizeof(uint16_t) + 1; i++) {
        fread(&currNum, sizeof(uint16_t), 1, file);
        fseek(file, -(i+1)*sizeof(uint16_t), SEEK_END);
        fwrite(&currNum, sizeof(uint16_t), 1, file);
        fseek(file, last_pos - (i+1)*sizeof(uint16_t), SEEK_SET);
    }

    int pos_read = 0;
    int pos_write = 0;
    fseek(file, mult*sizeof(uint16_t), SEEK_SET);
    pos_read = ftell(file);
    fread(&currNum, sizeof(uint16_t), 1, file);
    pos_read += sizeof(uint16_t);
    while (!feof(file)) {
        fseek(file, pos_write, SEEK_SET);
        fwrite(&currNum, sizeof(uint16_t), 1, file);
        pos_write += sizeof(uint16_t);
        currNum = ntohs(currNum);
        if ((currNum % 7) == 0) {
            currNum = htons(currNum);
            fwrite(&currNum, sizeof(uint16_t), 1, file);
            pos_write += sizeof(uint16_t);
        }
        fseek(file, pos_read, SEEK_SET);
        fread(&currNum, sizeof(uint16_t), 1, file);
        pos_read += sizeof(uint16_t);
    }

    fclose(file);

    return 0;
}
