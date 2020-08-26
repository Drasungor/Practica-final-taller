#include <stdio.h>
#include <stdint.h>

int main(int argc, const char* argv[]) {
    if (argc != 2) {
        printf("Cantidad de parametros invalida\n");
    }
    FILE* file = fopen(argv[1], "r+");
    if (!file) {
        printf("Archivo inexistente\n");
        return -1;
    }
    uint16_t aux;
    int numbers_to_append = 0;
    printf("Archivo original:\n");
    fread(&aux, sizeof(uint16_t), 1, file);
    while(!feof(file)) {
        printf("%u\n", aux);
        if (aux % 5 == 1) {
            numbers_to_append++;
        }
        fread(&aux, sizeof(uint16_t), 1, file);
    }
    //clearerr(file);
    fseek(file, 0, SEEK_END);
    int last_pos = ftell(file);
    uint16_t garbage = 0;

    //Agranda el archivo en la cantidad de bytes que se tienen que agregar
    for (int i = 0; i < numbers_to_append; i++) {
        fwrite(&garbage, sizeof(uint16_t), 1, file);
    }

    //Se corren los datos del archivo hacia el final, "llevando la basura" al
    //principio del archivo
    for (int i = 0; i < last_pos; ++i) {
        fseek(file, (last_pos - 1 - i) * sizeof(uint16_t), SEEK_SET);
        fread(&aux, sizeof(uint16_t), 1, file);
        fseek(file, -(i + 1) * sizeof(uint16_t), SEEK_END);
        fwrite(&aux, sizeof(uint16_t), 1, file);
    }
    clearerr(file);
    int i = 0;
    int written_numbers = 0;
    fseek(file, (numbers_to_append + i) * sizeof(uint16_t), SEEK_SET);
    fread(&aux, sizeof(uint16_t), 1, file);
    while (!feof(file)) {
        fseek(file, written_numbers * sizeof(uint16_t), SEEK_SET);
        written_numbers++;
        if (aux % 5 == 1) {
            fseek(file, written_numbers * sizeof(uint16_t), SEEK_SET);
            written_numbers++;
        }
        i++;
        fseek(file, (numbers_to_append + i) * sizeof(uint16_t), SEEK_SET);
        fread(&aux, sizeof(uint16_t), 1, file);
    }
    fseek(file, 0, SEEK_SET);
    printf("Archivo procesado\n", &aux);
    fread(&aux, sizeof(uint16_t), 1, file);
    while (!feof(file)) {
        printf("%u\n", &aux);
        fread(&aux, sizeof(uint16_t), 1, file);
    }
    fclose(file);
    return 0;
}
