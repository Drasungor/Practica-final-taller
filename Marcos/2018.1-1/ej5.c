/*Dentro del siguiente codigo:*/

int main(int argc, char* argv[]) {
    return 0;
}
/*
Defina:

a) Un puntero a entero sin signo a alocarse en el stack

b) Un arreglo para albergar 4 numeros de punto flotante que se aloque en el data segment.

c) Un caracter a alocarse en el data segment.
*/

/*a)*/

int main(int argc, char* argv[]) {
    unsigned int* myIntPtr = NULL;
    return 0;
}

/*b)*/

int main(int argc, char* argv[]) {
    static float myArray[4];
    return 0;
}

/*c)*/

int main(int argc, char* argv[]) {
    static char myChar = 0;
    return 0;
}