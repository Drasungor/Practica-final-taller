#include <stdio.h>
#include <string.h>
#include <stdlib.h>



int main(int argc, char** argv) {
    FILE* file = fopen(argv[1], "r+");
    if(!file) return -1;

    char line[100];
    fgets(line, 100, file);
    printf("%s\n", line);
    return 0;
}
