/*1) Escriba un programa que reciba por linea de comandos un Puerto y una IP.
El programa debe aceptar una unica conexion y recibir paquetes (cada paquete
inicia con '[' y finaliza con ']'). Para cada paquete recibido debe imprimir el
checksum (sumatoria de bytes del paquete) del mismo, excepto que el paquete este
vacio ('[]'), en cuyo caso debe finalizar.*/

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <netdb.h>
#include <string.h>
#include <sys/socket.h>

#define BUF_LEN 256
#define STOP_COND_LEN 3 //2 para la condicion y 1 para el \0

int processConnection(int fd) {
    char buffer[BUF_LEN];
    memset(buffer, 0, BUF_LEN*sizeof(char));
    int s = 0;
    unsigned int checksum = 0;
    char stopCondition[STOP_COND_LEN];
    char currByte = 0;
    int j = 0;
    memset(stopCondition, 0, STOP_COND_LEN*sizeof(char));

    while (strcmp(stopCondition, "[]")) {
        s = recv(fd, buffer, BUF_LEN, MSG_NOSIGNAL);
        if (s < 0) return 1;

        for (int i = 0; i < s; ++i) {
            currByte = buffer[i];
            if (currByte != '[' && currByte != ']') {
                memset(stopCondition, 0, STOP_COND_LEN*sizeof(char));
                j = 0;
                checksum += currByte;
            } else if (currByte == ']') {
                if (checksum != 0) {
                    printf("%u\n", checksum); /*separador para debuggear etc*/
                    checksum = 0;
                }
            } else { //currByte == '['
                memset(stopCondition, 0, STOP_COND_LEN*sizeof(char));
                j = 0;
            }
            stopCondition[j] = currByte;
            ++j;
        }

    }

    return 0;
}

int main(int argc, const char** argv) {
    if (argc < 3) return 1;
    const char* ip = argv[1];
    const char* port = argv[2];

    int s = 0, fd = -1;
    struct addrinfo hints;
    struct addrinfo *ai_list, *ptr;
    memset(&hints, 0, sizeof(struct addrinfo));

    hints.ai_family = AF_INET; /*IPv4*/
    hints.ai_socktype = SOCK_STREAM; /*TCP*/
    hints.ai_flags = 0; /*AI_PASSIVE para server*/

    s = getaddrinfo(ip, port, &hints, &ai_list);
    if (s != 0) {
        fprintf(stderr, "Error in getaddrinfo: %s\n", gai_strerror(s));
        return 1;
    }

    for (ptr = ai_list; ptr != NULL; ptr = ptr->ai_next) {
        fd = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
        if (fd == -1)
            continue;
        if (connect(fd, ptr->ai_addr, ptr->ai_addrlen) != -1)
            break;
        close(fd);
    }

    freeaddrinfo(ai_list);

    if (ptr == NULL) {
        fprintf(stderr, "Could not connect\n");
        return 1;
    }

    processConnection(fd);

    shutdown(fd, SHUT_RDWR);
    close(fd);

    return 0;
}