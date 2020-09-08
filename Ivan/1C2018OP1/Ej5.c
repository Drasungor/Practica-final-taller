/*Defina:

a) Un puntero a entero sin signo a alocarse en el stack

b) Un arreglo para albergar 4 numeros de punto flotante que se aloque en el data segment.

c) Un caracter a alocarse en el data segment.
*/


int main(int argc, char* argv[]) {
    unsigned int* i = NULL;
    static float array[4] = {1,2,3,4};
    static char a = 'a';
    return 0;
}
