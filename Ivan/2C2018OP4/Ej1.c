#define _POSIX_C_SOURCE 200112L

#include<string.h>
#include<stdbool.h>
#include <stdio.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

int main(int argc, char** argv) {
    struct addrinfo hints;
    struct addrinfo *ptr, *results;

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype  =  SOCK_STREAM;
    hints.ai_flags = 0;
    hints.ai_protocol = 0;

    int s;
    int skt = -1;

    const char* host = argv[1];
    const char* port = argv[2];

    s = getaddrinfo(host, port, &hints, &results);

    if(s != 0) return -1;

    for(ptr = results; ptr != NULL; ptr->ai_next) {
        skt = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
        if (skt == -1) continue;

        s = connect(skt, ptr->ai_addr, ptr->ai_addrlen);
        if(s != -1) break;

        close(skt);
    }

    freeaddrinfo(results);
    if(ptr == NULL) return -1;

    bool connected;
    char received;
    int checksum = 0;
    s = recv(skt, &received, 1, 0);
    connected = (s > 0);

    while (connected) {
        if (received == '[') {
            while(received != ']'){
                if (received != '[') checksum += received;
                s = recv(skt, &received, 1, 0);
                connected = (s > 0);
            }
            printf("%d\n", checksum);
        }

        if (checksum == 0) break;// Me llego el paquete vacio

        if(connected) {
            s = recv(skt, &received, 1, 0);
            connected = (s > 0);
            checksum = 0;
        }
    }

    shutdown(skt, SHUT_RDWR);
    close(skt);
}
