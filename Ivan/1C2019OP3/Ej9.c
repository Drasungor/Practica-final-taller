/*archivo de texto. Eliminar palabras de mas de 3 letras*/



int main(int argc, char const *argv[]) {
    FILE* file = fopen(argv[1], "r+");
    if (!file) {
        return -1;
    }

    char* line;

    while (!feof(file)) {
        fgets(line, 100, file);
        if (strlen(line) > 3) {
            
        }
    }

    return 0;
}
