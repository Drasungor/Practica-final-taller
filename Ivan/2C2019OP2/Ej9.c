#include<stdio.h>
#include<stdint.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char const *argv[]) {
    FILE* file = fopen(argv[1], "rb+");
    if(!file) return 0;

    uint16_t currNum;
    int removedAmount = 0;
    int numAmount = 0;

    fread(&currNum, sizeof(uint16_t), 1, file);

    while (!feof(file)) {
        
    }

    fseek(file, (numAmount + 1)*sizeof(uint16_t), SEEK_SET);
    ftruncate(fileno(file), ftell(file));
    fclose(file);
    return 0;
}
