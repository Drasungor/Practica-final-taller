/*9) Escriba un programa (desde la inicializacion hasta la liberacion de los
recursos) que reciba paquetes de texto delimitados por corchetes angulares
("<...>") y los imprima completos por pantalla. Al recibir un paquete vacio
("<>") debe cerrarse ordenadamente. No considere errores*/

#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cstring>
#include <netdb.h>

int processConnection(int fd) {
    int bytesRecv = 0;
    int s = 0;
    char byteRecv = 0;
    std::string stopCondition;
    std::string package;

    while (stopCondition != "<>") {

        stopCondition.clear();

        while (byteRecv != '>') {
            while (bytesRecv < 1) {
                s = recv(fd, &byteRecv, 1, MSG_NOSIGNAL);
                if (s < 1) return 1;
                bytesRecv += s; /*este while es re al pedo si leo de a 1 (xq si no hay error siempre lee al menos 1 byte el recv) pero lo hago por costumbre para memorizar*/
            }

            bytesRecv = 0;
            if (byteRecv == '<' || byteRecv == '>') {
                stopCondition.push_back(byteRecv);
            } else {
                stopCondition.clear();
                package.push_back(byteRecv);
            }
        }

        std::cout << package << std::endl; /*separo los paqutes en cada linea*/
        package.clear();
        byteRecv = 0;
    }

    return 0;
}

int main(int argc, const char** argv) {

    if (argc < 3) return 1;
    const char* ip = argv[1];
    const char* port = argv[2];

    struct addrinfo hints;
    struct addrinfo *ai_list, *ptr;

    int s = 0;
    int fd = -1;

    memset(&hints, 0, sizeof(struct addrinfo));

    hints.ai_family = AF_INET; /*IPv4*/
    hints.ai_socktype = SOCK_STREAM; /*TCP*/
    hints.ai_flags = 0; /*or AI_PASSIVE for server*/

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
        fprintf(stderr, "Error: could not connect\n");
        return 1;
    }

    int result = processConnection(fd);

    shutdown(fd, SHUT_RDWR);
    close(fd);

    return result;
}