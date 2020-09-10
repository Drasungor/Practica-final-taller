/*8) Escriba un programa que reciba por linea de comandos un Puerto y una IP.
El programa debe aceptar una unica conexion e imprimir en stdout todo lo
recibido. Al recibir el texto FIN debe finalizar el programa sin imprimir
dicho texto.*/

#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define BUF_SIZE 256
#define STOP_BUF_SIZE 4

bool processByte(char byte, char stopCondition[STOP_BUF_SIZE], int* j, bool* keepGoing) {
    if (byte == 'F' && *j == 0) {
        stopCondition[*j] = byte;
        ++(*j);
        return false;
    } else if (byte == 'I' && *j == 1) {
        stopCondition[*j] = byte;
        ++(*j);
        return false;
    } else if (byte == 'N' && *j == 2) {
        stopCondition[*j] = byte;
        *keepGoing = false;
        return false;
    }

    return true;
}

int processConnection(int fd) {
    int s = 0;
    int j = 0;
    char buffer[BUF_SIZE];
    memset(buffer, 0, BUF_SIZE);
    char stopCondition[STOP_BUF_SIZE];
    memset(stopCondition, 0, STOP_BUF_SIZE);
    bool keepGoing = true;

    while (keepGoing) {
        s = recv(fd, buffer, BUF_SIZE, MSG_NOSIGNAL);
        if (s < 1) {
            fprintf(stderr, "Connection closed unexpectedly!\n");
            return 1;
        }

        for (int i = 0; i < s; ++i) {
            if (processByte(buffer[i], stopCondition, &j, &keepGoing)) {
                for (int k = 0; k < j; ++k) {
                    printf("%#0x", stopCondition[k]);
                }
                memset(stopCondition, 0, STOP_BUF_SIZE);
                j = 0;
                printf("%#0x", buffer[i]);
            }
        }

        fflush(stdout);
    }


    return s;
}

int main(int argc, char** argv) {
    if (argc < 3) return 1;
    const char* ip = argv[1];
    const char* port = argv[2];

    int s = 0;
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
        fprintf(stderr, "Could not connect!\n");
        return 1;
    }

    s = processConnection(fd);

    shutdown(fd, SHUT_RDWR);
    close(fd);
    return s;
}