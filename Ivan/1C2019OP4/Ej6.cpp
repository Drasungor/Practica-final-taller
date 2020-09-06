#define _POSIX_C_SOURCE 200112L


#include <cstring>
#include <iostream>

#include<string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

int main(int argc, char const *argv[]) {
    struct addrinfo hints;
    struct addrinfo *ptr, *results;

    const char* host = argv[1];
    const char* port = argv[2];

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = 0;
    hints.ai_protocol = 0;

    int s = getaddrinfo(host, port, &hints, &results);
    if (s != 0) return -1;

    int skt = -1;

    for (ptr = results; ptr != NULL; ptr->ai_next) {
        skt = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
        if (skt == -1) continue;

        s = connect(skt, ptr->ai_addr, ptr->ai_addrlen);
        if (s != -1) break;

        close(skt);
    }

    freeaddrinfo(results);

    if (ptr == NULL) return -1;


    char received;
    char buff[4];
    int buff_index = 0;
    bool receiving_end = false;
    bool connected = true;
    s = recv(skt, &received, 1, MSG_NOSIGNAL);
    connected = (s > 0);
    // while (connected) {
    //     if (received == 'F') {
    //         buff[0] = 'F';
    //         s = recv(skt, (buff + 1), 2, MSG_NOSIGNAL);
    //         if (s <= 0) {
    //             connected = false;
    //             break;
    //         }
    //         if (buff[1] == 'I' && buff[2] == 'N') {
    //             connected = false;
    //         } else {
    //             for (size_t i = 0; i < 3; i++) {
    //                 printf("%c\n", *(buff + i));
    //             }
    //         }
    //     } else {
    //         printf("%c\n", received);
    //     }
    //
    //     if (connected) {
    //         s = recv(skt, &received, 1, MSG_NOSIGNAL);
    //         connected = (s > 0);
    //     }
    // }

    while (connected) {
        if (received == 'F') {
            if (buff_index == 1) {
                printf("F\n");//Si ya habia recibido una F
            }
            buff_index = 0;
            receiving_end = true;
            memset(&buff, 0, 3);
            buff[buff_index] = 'F';
            ++buff_index;
        } else if (received == 'I' && buff_index == 1) {
            buff[buff_index] = 'I';
            ++buff_index;
        } else if (received == 'N' && buff_index == 2) {
            buff[buff_index] = 'N';
            ++buff_index;
            buff[buff_index] = '\0';
            if (strncmp(buff, "FIN", 3) == 0) {
                connected = false;
            }
        } else if (buff_index >= 2) {
            receiving_end = false;
            for (size_t i = 0; i < buff_index; i++) {
                printf("%c\n", *(buff + i));
            }
            buff_index = 0;
            memset(&buff, 0, 3);
        }

        if (!receiving_end) {
            printf("%c\n", received);
        }

        if (connected) {
            s = recv(skt, &received, 1, MSG_NOSIGNAL);
            connected = (s > 0);
        }
    }

    shutdown(skt, SHUT_RDWR);
    close(skt);
    return 0;
}
