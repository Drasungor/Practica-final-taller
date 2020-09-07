/*9) Escriba un programa que reciba paquetes de 10 bytes por el puerto TCP 815 y los
imprima por pantalla. Al recibir el byte 0xff debe cerrarse ordenadamente.
No considere errores.*/

/*Asumo que es byte no viene en un paquete, es decir, es un byte por separado*/

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <netdb.h>
#include <string.h>
#include <sys/socket.h>
#include <stdbool.h>

#define PACKAGE_SIZE 10

int processConnection(int fd) {
    char package[PACKAGE_SIZE];
    memset(package, 0, PACKAGE_SIZE);
    int bytesReceived = 0;
    int s = 0;
    bool keepGoing = true;

    while (keepGoing) {

        while (bytesReceived < PACKAGE_SIZE && keepGoing) {
            s = recv(fd, package + bytesReceived, PACKAGE_SIZE - bytesReceived, MSG_NOSIGNAL);
            if (s < 1) return 1;
            if (package[0] == 0xff) {
                keepGoing = false;
            }
            bytesReceived += s;
        }

        if (keepGoing) {
            bytesReceived = 0;
            for (int i = 0; i < PACKAGE_SIZE; ++i) {
                printf("%#x", package[i]);
            }
            memset(package, 0, PACKAGE_SIZE);
            printf("\n");
        }

    }


    return 0;
}

int main(int argc, char** argv) {
    if (argc < 3) return 1;
    const char* ip = argv[1];
    const char* port = argv[2];

    int s;
    int fd = -1;

    struct addrinfo hints;
    struct addrinfo* ai_list, *ptr;
    memset(&hints, 0, sizeof(struct addrinfo));

    hints.ai_family = AF_INET; /*IPv4*/
    hints.ai_socktype = SOCK_STREAM; /*TCP*/
    hints.ai_flags = 0; /*AI_PASSIVE for server*/

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
        fprintf(stderr, "Error in connect\n");
        return 1;
    }

    s = processConnection(fd);

    shutdown(fd, SHUT_RDWR);
    close(fd);

    return s;
}