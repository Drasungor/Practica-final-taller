/*7) Escriba un programa que reciba por linea de comandos un puerto y una IP.
El programa debe aceptar una unica conexion e imprimir en stdout la sumatoria
de los enteros recibidos en cada paquete. Un paquete esta definido como una
sucesion de numeros recibidos como texto, en decimal, separados or comas y terminado
con un signo igual (ej:  " 27,12,32="). Al recibir el texto 'FIN' debe finalizar el
programa oredenadamente liberando los recursos*/

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define BUF_SIZE 256

int setUpConnection(const char* port, const char* ip) {
        struct addrinfo hints;
        struct addrinfo *ai_list, *ptr;
        int fd = -1;

        memset(&hints, 0, sizeof(struct addrinfo));
        hints.ai_family = AF_INET; /* IPv4 (or AF_INET6 for IPv6)*/
        hints.ai_socktype = SOCK_STREAM; /*TCP*/
        hints.ai_flags = 0; /*AI_PASSIVE for Server*/

        int s = getaddrinfo(port, ip, &hints, &ai_list); /*me devuelve las direcciones conseguidas en ai_list*/
        if (s != 0) {
            printf("Error in getaddrinfo: %s\n", gai_strerror(s));
            return -1;
        }

        for (ptr = ai_list; ptr != NULL; ptr = ptr->ai_next) {
                   fd = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
                   if (fd == -1)
                       continue;

                   if (connect(fd, ptr->ai_addr, ptr->ai_addrlen) != -1)
                       break;                  /* Success */

                   close(fd);
                   fd = -1;
        }

        freeaddrinfo(ai_list); /*Lo libero porque no lo necesito mas*/
        return fd;
}

int processConnection(int fd) {
    char byteRecv = 0;
    char currNumber[BUF_SIZE];
    char exitCondition[BUF_SIZE];
    int bytes = 0; /*para ver cuantos bytes recibi*/
    int flag = 0;
    int i = 0, j = 0;
    int sum = 0;
    memset(currNumber, 0, sizeof(char)*BUF_SIZE);
    memset(exitCondition, 0, sizeof(char)*BUF_SIZE);

    while (strcmp(exitCondition, "FIN")) {

        while (byteRecv != '=') {
            while (bytes < 1) {
                flag = recv(fd, &byteRecv, 1, MSG_NOSIGNAL); /*el 0 es para los flags*/
                if (flag < 0) return -1;
                bytes += flag;
            }

            bytes = 0;
            if ('0' <= byteRecv && byteRecv <= '9') {
                memset(exitCondition, 0, sizeof(char)*BUF_SIZE);
                j = 0;
                currNumber[i] = byteRecv;
                ++i;
            } else if (byteRecv == ',' || byteRecv == '=') {
                memset(exitCondition, 0, sizeof(char)*BUF_SIZE);
                j = 0;
                currNumber[i] = '\0'; /*sino atoi rompe rico*/
                i = 0;
                sum += atoi(currNumber);
            } else {
                exitCondition[j] = byteRecv;
                exitCondition[j+1] = '\0';
                if (!strcmp(exitCondition, "FIN")) break;
                ++j;
            }

        }

        printf("La sumatoria del paquete es %d\n", sum);
        byteRecv = 0;
        sum = 0;
    }

}

int main(int argc, char** argv) {
    /*acordarse de chequear errores*/
    const char* port = argv[1];
    const char* ip = argv[2];
    int fd = setUpConnection(port, ip);
    if (fd == -1) return 1; /*no logre conectarme*/

    processConnection(fd);


    close(fd);


    return 0;
}
