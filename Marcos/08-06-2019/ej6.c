/*6) Escriba un programa que reciba por linea de comandos un Puerto y una IP.
El programa debe aceptar una unica conexion e imprimir en stdout todo lo recibido.
Al recibir el texto 'FIN' debe finalizar el programa sin imprimir dicho texto.*/

#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <stdbool.h>

#define STOP_BUFF_SIZE 4
#define DONT_PRINT 1
#define PRINT_BUFFER 2

int addToStop(char stopCondition[STOP_BUFF_SIZE], int* i, char c, bool* stop) {
    int flag = DONT_PRINT;
    if (c == 'F') {
        memset(stopCondition, 0, STOP_BUFF_SIZE);
        *i = 0;
        stopCondition[*i] = c;
        ++(*i);
    } else if (c == 'I' && *i == 1) {
        stopCondition[*i] = c;
        ++(*i);
    } else if (c == 'N' && *i == 2) {
        stopCondition[*i] == c;
        *stop = true;
    } else {
        *i = 0;
        flag = PRINT_BUFFER;
    }
    return flag;
}

int proccessConnection(int fd) {
    char byteRecv = 0;
    char stopCondition[STOP_BUFF_SIZE];
    int bytes = 0;
    int s = 0;

    int i = 0;
    bool stop = false;

    memset(stopCondition, 0, STOP_BUFF_SIZE);

    while (!stop) {

        while (bytes < 1) {
            s = recv(fd, &byteRecv, 1, MSG_NOSIGNAL);
            if (s < 1) return 1;
            bytes += s;
        }

        bytes = 0;
        s = addToStop(stopCondition, &i, byteRecv, &stop);
        if (s == PRINT_BUFFER) {
            printf("%s", stopCondition);
            printf("%c", byteRecv);
            fflush(stdout);
            memset(stopCondition, 0, STOP_BUFF_SIZE);
        }
    }
}

int main(int argc, char** argv) {

    if (argc < 3) return 1;
    char* ip = argv[1];
    char* port = argv[2];
    int fd = -1;
    int s = 0;
    struct addrinfo hints;
    struct addrinfo *ai_list, *ptr;
    memset(&hints, 0, sizeof(struct addrinfo));

    hints.ai_family = AF_INET; /*IPv4*/
    hints.ai_socktype = SOCK_STREAM; /*TCP*/
    hints.ai_flags = 0; /*AI_PASSIVE for server*/

    s = getaddrinfo(ip, port, &hints, &ai_list);
    if (s != 0) {
        printf("Error in getaddrinfo: %s\n", gai_strerror(s));
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
        printf("Could not connect\n");
        return 1;
    }

    proccessConnection(fd);


    shutdown(fd, SHUT_RDWR);
    close(fd);

    return 0;
}