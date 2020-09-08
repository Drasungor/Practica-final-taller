/*4) Defina una rutina en C que se conecte a la IP 8.8.8.8, al puerto 8192 y
reciba un archivo binario. El archivo recibido debe ser descargado a un archivo
llamado recibido.bin cuidando el uso de recursos de memoria.
El archivo finaliza al detectar conexion cerrada.*/

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <string.h>
#include <netdb.h>
#include <stdbool.h>

#define BUF_SIZE 256

int processConnection(int fd) {
    FILE* file = fopen("recibido.bin", "wb+");
    char buffer[BUF_SIZE];
    memset(buffer, 0, BUF_SIZE);
    bool keepGoing = true;
    int s = 0;

    while (keepGoing) {

        s = recv(fd, buffer, BUF_SIZE, MSG_NOSIGNAL);
        if (s < 0) {
            fclose(file);
            return 1;
        } else if (s == 0) {
            keepGoing = false;
        } else {
            fwrite(buffer, sizeof(char), s, file);
            memset(buffer, 0, BUF_SIZE);
        }

    }

    fclose(file);
    return 0;
}

int main (int argc, char** argv) {
    //const char* ip = "8.8.8.8"; /*Esto es lo que habria q hacer pero no lo pongo para poder probar lo mio*/
    //const char* port = "8192";
    if (argc < 3) return 1;
    const char* ip = argv[1];
    const char* port = argv[2];

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