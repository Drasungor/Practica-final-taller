#include<stdio.h>
#include<stdint.h>

int main(int argc, char const *argv[]) {
    FILE* file = fopen(argv[1], "rb+");

    if(!file) return -1;

    uint16_t curr_num;

    fread(&curr_num, sizeof(uint16_t), 1, file);
    while (!feof(file)) {
        printf("%d\n", curr_num);
        if ((curr_num % 3) == 0) {
            curr_num *= 2;
            fseek(file, -sizeof(uint16_t), SEEK_CUR);
            fwrite(&curr_num, sizeof(uint16_t), 1, file);
        }
        fread(&curr_num, sizeof(uint16_t), 1, file);
    }

    fclose(file);

    return 0;
}
